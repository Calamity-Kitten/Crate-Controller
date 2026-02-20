#include "game.h"

static unsigned char gameMode = GAME_MODE_OFF;

static unsigned int minimumTime = DEFAULT_MINIMUM_TIME;
static unsigned int maximumTime = DEFAULT_MAXIMUM_TIME;

void setGameMode(unsigned char newGameMode) {
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

unsigned int getMinimumTime() {
  Serial.printf(" - Minimum time: %d\n", minimumTime);
  return minimumTime;
}

void setMinimumTime(unsigned int newMinimumTime) {
  if (newMinimumTime < MINIMUM_TIME_MIN) newMinimumTime = MINIMUM_TIME_MIN;
  else if (newMinimumTime > MINIMUM_TIME_MAX) newMinimumTime = MINIMUM_TIME_MAX;
  
  minimumTime = newMinimumTime;
}