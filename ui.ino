#include "ui.h"

#include "config.h"

static LED buffer_[UI_BUFFER_SIZE] = {};
static size_t start_ = 0;
static size_t end_ = 0;

void led_buffer_add(struct LED action) {
 if (end_ == UI_BUFFER_SIZE)
  {
    if (start_ > 0)
      buffer_[--start_] = action;
    else {
      // Must not be happened
      return;
    }
  }
  else
    buffer_[end_++] = action;
  return 0;
}

void led_buffer_update()
{
  unsigned long time = millis();

  for (size_t i = start_; i < end_; i++) {
    auto& led = buffer_[i];
    if ((led.led == 0) || (time < led.timing))
      continue;

    digitalWrite(led.led, led.level);
    led.led = 0;
    start_ += i == start_;
  }

  if (start_ == end_)
  {
    start_ = 0;
    end_ = 0;
  }
}