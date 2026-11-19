#include "target.h"
#include "ui.h"
#include "config.h"
#include "timeattack.h"

bool setup_status_ = false;

void setup() {
  setup_status_ = true;
  Serial.begin(9600);
  Serial.println("START SETUP");

  Serial.println("CHECKING LED");
  // Check LEDs working well.
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < NTARGETS; j++)
      digitalWrite(TARGETS[j].led(), HIGH);
    delay(250);
    for (int j = 0; j < NTARGETS; j++)
      digitalWrite(TARGETS[j].led(), LOW);
    delay(250);
  }
  Serial.println("CHECKED LED");

  Serial.println("CHECKING SENSOR");
  for (int i = 0; i < NTARGETS; i++) {
    int state = digitalRead(TARGETS[i].sensor());
    if (state == LOW)
      setup_status_ = false; // Should not be happened.
  }
  if (setup_status_)
    Serial.println("CHECKED SENSOR");
  else
    Serial.println("CHECKING SENSOR FAILED");

  GAME_SETUP();
}

void loop() {
  if (!setup_status_) {
    delay(1000);
    return;
  }
  GAME_UPDATE();
  led_buffer_update();
  delay(10);
}