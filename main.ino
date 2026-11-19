#include "target.h"
#include "config.h"

LEDBuffer g_led_buffer(LED_BUFFER_SIZE);
Target targets[] = {Target(4, 3)};
Game *game;

void setup() {
  Serial.begin(9600);
  game = new GameTimeattack(targets, sizeof(targets) / sizeof(targets[0]), 20);
}

void loop() {
  game->update();
  g_led_buffer.update();
  delay(10);
}