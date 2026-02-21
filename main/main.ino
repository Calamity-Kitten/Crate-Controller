#include "config.h"

void setup() {
  // put your setup code here, to run once:
  initHardware();
  initWiFi();

  setGameMode(GAME_MODE_BASIC_STATIC);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateGame();
  updateWiFi();
}