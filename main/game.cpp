#include "game.h"

static unsigned char gameMode = GAME_MODE_OFF;

void changeGameMode(unsigned char newGameMode) {
  if (gameMode == newGameMode) {
    // TODO: Should this reset the game?
    return;
  }

  gameMode = newGameMode;
}

void updateGame() {
  if (gameMode == GAME_MODE_OFF) {
    clearButtonLED();
  } else if (gameMode == GAME_MODE_BASIC) {
    setButtonLED(getRainbowRGB());
  }
}