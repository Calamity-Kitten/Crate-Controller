#include "game.h"

static unsigned char gameMode = GAME_MODE_OFF;

void updateGame() {
  if (gameMode == GAME_MODE_OFF) {
    clearButtonLED();
  }
}