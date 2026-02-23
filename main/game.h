#ifndef game_h
#define game_h

#include <Arduino.h>
#include "config.h"

#define GAME_MODE_OFF 0
#define GAME_MODE_BASIC_STATIC 1
#define GAME_MODE_BASIC_RANDOM 2

#define DEFAULT_GAME_MODE GAME_MODE_OFF

#define DEFAULT_MINIMUM_TIME 300000 // Five Minutes
#define MINIMUM_TIME_MIN 60000 // One minute
#define MINIMUM_TIME_MAX 900000 // Fifteen Minutes

#define DEFAULT_MAXIMUM_TIME 600000 // Ten Minutes
#define MAXIMUM_TIME_MIN 600000
#define MAXIMUM_TIME_MAX 900000

#define DEFAULT_STATIC_TIME 300000 // Five Minutes
#define STATIC_TIME_MIN 60000
#define STATIC_TIME_MAX 900000

void updateGame();

unsigned char getGameMode();
void setGameMode(unsigned char newGameMode);
unsigned int getMaximumTime();
void setMaximumTime(unsigned int newMaximumTime);
unsigned int getMinimumTime();
void setMinimumTime(unsigned int newMinimumTime);
unsigned int getStaticTime();
void setStaticTime(unsigned int newStaticTime);

#endif