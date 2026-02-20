#ifndef game_h
#define game_h

#include <Arduino.h>
#include "config.h"

#define GAME_MODE_OFF 0
#define GAME_MODE_BASIC 1

#define DEFAULT_MINIMUM_TIME 300000 // Five Minutes
#define MINIMUM_TIME_MIN 60000 // One minute
#define MINIMUM_TIME_MAX 900000 // Fifteen Minutes
#define DEFAULT_MAXIMUM_TIME 600000 // Ten Minutes
#define MAXIMUM_TIME_MIN 60000
#define MAXIMUM_TIME_MAX 900000

void setGameMode(unsigned char newGameMode);
void updateGame();

unsigned int getMaximumTime();
void setMaximumTime(unsigned int newMaximumTime);
unsigned int getMinimumTime();
void setMinimumTime(unsigned int newMinimumTime);

#endif