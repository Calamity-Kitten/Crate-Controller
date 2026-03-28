#include "config.h"

void setup() {
  initHardware();
  initDisplay();
  initSettings();
  initWiFi();
}

void loop() {
  updateDisplay();
  updateGame();
}