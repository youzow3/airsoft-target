
#include "target.h"

Target::Target(uint8_t led, uint8_t sensor) : led_(led), sensor_(sensor), last_fired_(0) {
  pinMode(led_, OUTPUT);
  pinMode(sensor_, INPUT);
}

bool Target::update() {
  int state = digitalRead(sensor_);
  if (state == HIGH)
    return false;
  last_fired_ = millis();
  return true;
}

GameTimeattack::GameTimeattack(Target *targets, size_t ntargets, size_t count) : Game(targets, ntargets), sequence_(new int[count]), count_(count), step_(0), stepped_(true) {
  for (size_t i = 0; i < count_; i++)
    sequence_[i] = random(0, ntargets_);
}

bool GameTimeattack::update() {
  if (step_ == count_)
    return false;

  if (stepped_)
  {
    unsigned long time = millis();

    if (step_ > 0)
    {
      uint8_t led = targets_[sequence_[step_ - 1]].led();
      g_led_buffer.add(new LED{led, LOW, time});
      g_led_buffer.add(new LED{led, HIGH, time + 200});
      g_led_buffer.add(new LED{led, LOW, time + 400});
      g_led_buffer.add(new LED{led, HIGH, time + 600});
      g_led_buffer.add(new LED{led, LOW, time + 800});
    }
    g_led_buffer.add(new LED{targets_[sequence_[step_]].led(), HIGH, time});
    stepped_ = false;
  }

  if (!targets_[sequence_[step_]].update())
    return false;
  
  step_++;
  stepped_ = true;
  return true;
}

LEDBuffer::LEDBuffer(size_t buffer_size) : buffer_(new LED*[buffer_size]), buffer_size_(buffer_size), start_(0), end_(0) {
  for (size_t i = 0; i < buffer_size; i++)
    buffer_[i] = nullptr;
}

void LEDBuffer::add(const LED *led) {
  if (end_ == buffer_size_) {
    Serial.println("LEDBuffer::add fail: Not enough buffer size.");
    return;
  }
  buffer_[end_++] = led;
}

bool LEDBuffer::update()
{
  bool updated = false;
  unsigned long time = millis();
  for (size_t i = start_; i < end_; i++)
  {
    const LED *led = buffer_[i];
    if ((led == nullptr) || (led->timing > time))
      continue;
    digitalWrite(led->led, led->level);
    delete buffer_[i];
    buffer_[i] = nullptr;
    start_ += i == start_;
    updated = true;
  }

  if (start_ == end_)
  {
    start_ = 0;
    end_ = 0;
  }

  return updated;
}
