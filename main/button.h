#ifndef button_h
#define button_h

#include <Arduino.h>
#include "config.h"

#define DEBOUNCE_TIME 50

bool checkButton();

#endif //button_h