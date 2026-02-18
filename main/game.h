#ifndef game_h
#define game_h

#include <Arduino.h>
#include "config.h"

#define GAME_MODE_OFF 0
#define GAME_MODE_BASIC 1

void setGameMode(unsigned char newGameMode);
void updateGame();

#endif