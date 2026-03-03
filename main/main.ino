#include "config.h"

void setup() {
  // put your setup code here, to run once:
  initHardware();
  initDisplay();
  initWiFi();
  initSettings();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay();
  updateGame();
  updateWiFi();
}