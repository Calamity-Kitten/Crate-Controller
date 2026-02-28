#include "game.h"

static unsigned char gameMode = DEFAULT_GAME_MODE;

static unsigned int minimumTime = DEFAULT_MINIMUM_TIME;
static unsigned int maximumTime = DEFAULT_MAXIMUM_TIME;
static unsigned int staticTime = DEFAULT_STATIC_TIME;

static int nextPress;
static int minRand = maximumTime;
static int maxRand = minimumTime;

void updateGame() {
  switch(gameMode) {
    case GAME_MODE_BASIC_STATIC:
      updateGame_BasicStatic();
      break;
    case GAME_MODE_BASIC_RANDOM:
      updateGame_BasicRandom();
      break;
    case GAME_MODE_OFF:
    default:
      setButtonLED(getRainbowRGB());
      // clearButtonLED();
      break;
  }
}

void updateGame_BasicStatic() {
  if (millis() < nextPress) return;

  setButtonLED({.r = 245.0/255.0, .g=169.0/255.0, .b=184.0/255.0});
  
  if (checkButton()) {
    clearButtonLED();
    //TODO: Log press
    resetButtonTimer_BasicStatic();
  }
}

void updateGame_BasicRandom() {
  if (millis() < nextPress) return;

  setButtonLED(getRainbowRGB());

  if (checkButton()) {
    clearButtonLED();
    // TODO: Log press
    resetButtonTimer_BasicRandom();
  }
}

void resetButtonTimer_BasicStatic() {
  nextPress = millis() + staticTime;
  if (DEBUG) Serial.printf("Next press: %d\n", nextPress);
  clearButtonLED();
}

void resetButtonTimer_BasicRandom() {
  int randomTime = minimumTime + (int)((float)esp_random() * (float)(maximumTime - minimumTime) /  (float)UINT32_MAX);
  nextPress = millis() + randomTime;
  if (DEBUG) Serial.printf("Next press: %d\n", nextPress);
  clearButtonLED();
}

unsigned int getMinimumTime() {
  if (DEBUG) Serial.printf(" - Minimum time: %d\n", minimumTime);
  return minimumTime;
}

void setMinimumTime(unsigned int newMinimumTime) {
  if (newMinimumTime < MINIMUM_TIME_MIN) newMinimumTime = MINIMUM_TIME_MIN;
  else if (newMinimumTime > MINIMUM_TIME_MAX) newMinimumTime = MINIMUM_TIME_MAX;
  
  minimumTime = newMinimumTime;
}

unsigned int getMaximumTime() {
  if (DEBUG) Serial.printf(" - Maximum time: %d\n", maximumTime);
  return maximumTime;
}

void setMaximumTime(unsigned int newMaximumTime) {
  if (newMaximumTime < MAXIMUM_TIME_MIN) newMaximumTime = MAXIMUM_TIME_MIN;
  else if (newMaximumTime > MAXIMUM_TIME_MAX) newMaximumTime = MAXIMUM_TIME_MAX;
  
  maximumTime = newMaximumTime;
}

unsigned int getStaticTime() {
  if (DEBUG) Serial.printf(" - Static time: %d\n", staticTime);
  return staticTime;
}

void setStaticTime(unsigned int newStaticTime) {
  if (newStaticTime < STATIC_TIME_MIN) newStaticTime = STATIC_TIME_MIN;
  else if (newStaticTime > STATIC_TIME_MAX) newStaticTime = STATIC_TIME_MAX;
  
  staticTime = newStaticTime;
}

unsigned char getGameMode() {
  if (DEBUG) {
    Serial.print(" - Game Mode: ");
    switch(gameMode) {
      case 0:
        Serial.println("Off");
        break;
      case 1:
        Serial.println("Basic - Static");
        break;
      case 2:
        Serial.println("Basic - Random");
        break;
    }
  }
  return gameMode;
}

void setGameMode(unsigned char newGameMode) {
  unsigned oldGameMode = gameMode;
  // if (gameMode >= 0 && gameMode <= 2) gameMode = newGameMode;
  // else gameMode = 0;
  if (DEBUG) Serial.printf("Old: %d, New: %d\n", oldGameMode, newGameMode);

  // Do nothing if game mode hasn't changed
  if (oldGameMode == newGameMode) return;

  // TODO: Initialize game
  switch(newGameMode) {
    case 1:
      if (DEBUG) Serial.println("Start new game (Basic - Static)");
      gameMode = GAME_MODE_BASIC_STATIC;
      resetButtonTimer_BasicStatic();
      break;
    case 2:
      if (DEBUG) Serial.println("Start new game (Basic - Random)");
      gameMode = GAME_MODE_BASIC_RANDOM;
      resetButtonTimer_BasicRandom();
      break;
    case 0:
    default:
      if (DEBUG) Serial.println("Turn game off");
      gameMode = GAME_MODE_OFF;
      break;
  }
}