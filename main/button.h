#ifndef button_h
#define button_h

#include <Arduino.h>
#include "config.h"

#define DEBOUNCE_TIME 100

void checkButton();
void buttonPress();

#endif //button_h