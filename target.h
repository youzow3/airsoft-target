#pragma once

class Target {
  public:
    Target(uint8_t led, uint8_t sensor);
    bool update();
    uint8_t led() { return led_; }
    uint8_t sensor() { return sensor_; }
    unsigned long last_fired() { return last_fired_; }
  private:
    uint8_t led_;
    uint8_t sensor_;
    unsigned long last_fired_;
};