#include "target.h"
#include "ui.h"
#include "config.h"
#include "timeattack.h"

void setup() {
  Serial.begin(9600);
  timeattack_setup();
}

void loop() {
  timeattack_update();
  led_buffer_update();
  delay(10);
}