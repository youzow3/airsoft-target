#pragma once

struct LED {
  uint8_t led; // Pin number
  int level; // HIGH or LOW
  unsigned long timing; // Absolute timing in milliseconds.
};

void led_buffer_add(struct LED led);
void led_buffer_update();