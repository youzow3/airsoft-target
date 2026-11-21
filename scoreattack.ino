
#include "scoreattack.h"

namespace ScoreAttack
{
static unsigned long start_;
static unsigned long step_;
static bool stepped_;
static size_t last_target_;
static size_t target_;
static bool result_;

void setup()
{
  start_ = millis();
  step_ = 0;
  stepped_ = false;
  target_ = random(0, NTARGETS);
  result_ = false;
  Serial.print("1st target: ");
  Serial.println(target_);
}

void update()
{
  unsigned long time = millis();

  if (stepped_) {
    Serial.println("Handling LED emition");
    if (step_ > 0) {
      Serial.print("LOWing last target: ");
      Serial.println(last_target_);
      uint8_t led = TARGETS[last_target_].led();
      led_buffer_add({led, LOW, time});
      led_buffer_add({led, HIGH, time + 200});
      led_buffer_add({led, LOW, time + 400});
      led_buffer_add({led, HIGH, time + 600});
      led_buffer_add({led, LOW, time + 800});
    }

    Serial.print("HIGHing next target");
    Serial.println(target_);
    led_buffer_add({TARGETS[target_].led(), HIGH, time});
    stepped_ = false;
  }

  if ((time - start_) > SCOREATTACK_DURATION)
  {
    if (result_)
      return;
    led_buffer_add({TARGETS[target_].led(), LOW, time + 100});
    Serial.print("Finished: ");
    Serial.print(step_);
    Serial.println(" targets");
    result_ = true;
    return;
  }

  if (!TARGETS[target_].update())
    return;

  step_++;
  stepped_ = true;
  last_target_ = target_;
  while (last_target_ == target_)
    target_ = random(0, NTARGETS);
  Serial.print("Next target: ");
  Serial.println(target_);
}
}