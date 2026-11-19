#include "timeattack.h"

#include "ui.h"
#include "config.h"
#include "target.h"

static size_t targets_[TIMEATTACK_N_TARGETS];
static size_t step_;
static bool stepped_;
static unsigned long start_time_;
static bool result_;

void timeattack_setup()
{
  for (size_t i = 0; i < TIMEATTACK_N_TARGETS; i++)
    targets_[i] = random(0, NTARGETS);
  step_ = 0;
  stepped_ = true;
  start_time_ = millis();
  result_ = false;
}

void timeattack_update()
{
  if (stepped_)
  {
    unsigned long time = millis();

    if (step_ > 0)
    {
      uint8_t led = TARGETS[targets_[step_ - 1]].led();
      led_buffer_add({led, LOW, time});
      led_buffer_add({led, HIGH, time + 200});
      led_buffer_add({led, LOW, time + 400});
      led_buffer_add({led, HIGH, time + 600});
      led_buffer_add({led, LOW, time + 800});
    }

    if (step_ < TIMEATTACK_N_TARGETS)
      led_buffer_add({TARGETS[targets_[step_]].led(), HIGH, time});
    stepped_ = false;
  }

  if (step_ == TIMEATTACK_N_TARGETS)
  {
    if (result_)
      return;
    Serial.print("Finish: ");
    Serial.print(millis() - start_time_);
    Serial.print(" milliseconds");
    result_ = true;
  }

  if (!TARGETS[targets_[step_]].update())
    return false;
  
  step_++;
  stepped_ = true;
  return true;
}