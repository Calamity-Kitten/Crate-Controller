#ifndef button_h
#define button_h

#include "config.h"

#define DEBOUNCE_TIME 50

// Checks button state, returns true once on initial press.
// Sets `debounce` to `millis() + DEBOUNCE_TIME`, will not return false 
// before time threshold held by `debounce`.
bool checkButton();

#endif //button_h