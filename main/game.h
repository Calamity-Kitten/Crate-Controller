#ifndef game_h
#define game_h

#include <Arduino.h>
#include <esp_system.h>
#include "config.h"

#define GAME_MODE_OFF 0
#define GAME_MODE_BASIC_STATIC 1
#define GAME_MODE_BASIC_RANDOM 2

#define DEFAULT_GAME_MODE GAME_MODE_OFF
#define MINIMUM_GAME_MODE 0
#define MAXIMUM_GAME_MODE 2

#define DEFAULT_MINIMUM_TIME 5 * 60 * 1000 
#define MINIMUM_TIME_MIN 1 * 60 * 1000
#define MINIMUM_TIME_MAX 15 * 60 * 1000

#define DEFAULT_MAXIMUM_TIME 10 * 60 * 1000
#define MAXIMUM_TIME_MIN 1 * 60 * 1000
#define MAXIMUM_TIME_MAX 15 * 60 * 1000

#define DEFAULT_STATIC_TIME 5 * 60 * 1000
#define STATIC_TIME_MIN 1 * 60 * 1000
#define STATIC_TIME_MAX 15 * 60 * 1000

void updateGame();

void updateGame_BasicStatic();
void updateGame_BasicRandom();
void resetButtonTimer_BasicStatic();
void resetButtonTimer_BasicRandom();

unsigned char getGameMode();
void setGameMode(unsigned char newGameMode);
unsigned int getMaximumTime();
void setMaximumTime(unsigned int newMaximumTime);
unsigned int getMinimumTime();
void setMinimumTime(unsigned int newMinimumTime);
unsigned int getStaticTime();
void setStaticTime(unsigned int newStaticTime);
unsigned int getNextPress();

#endif