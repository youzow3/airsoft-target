
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