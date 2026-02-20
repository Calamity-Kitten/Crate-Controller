#include "game.h"

static unsigned char gameMode = GAME_MODE_OFF;

static unsigned int minimumTime = DEFAULT_MINIMUM_TIME;
static unsigned int maximumTime = DEFAULT_MAXIMUM_TIME;
static unsigned int staticTime = DEFAULT_STATIC_TIME;

static int nextPress;

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

unsigned int getMaximumTime() {
  Serial.printf(" - Maximum time: %d\n", maximumTime);
  return maximumTime;
}

void setMaximumTime(unsigned int newMaximumTime) {
  if (newMaximumTime < MAXIMUM_TIME_MIN) newMaximumTime = MAXIMUM_TIME_MIN;
  else if (newMaximumTime > MAXIMUM_TIME_MAX) newMaximumTime = MAXIMUM_TIME_MAX;
  
  maximumTime = newMaximumTime;
}

unsigned int getStaticTime() {
  Serial.printf(" - Static time: %d\n", staticTime);
  return staticTime;
}

void setStaticTime(unsigned int newStaticTime) {
  if (newStaticTime < STATIC_TIME_MIN) newStaticTime = STATIC_TIME_MIN;
  else if (newStaticTime > STATIC_TIME_MAX) newStaticTime = STATIC_TIME_MAX;
  
  staticTime = newStaticTime;
}