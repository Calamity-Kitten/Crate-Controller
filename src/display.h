#ifndef display_h
#define display_h

#include <Adafruit_SSD1306.h>
#include "config.h"

// Establish basic display settings (orientation & power) and
// load splash screen
void initDisplay();

// Draws calamity kitten logo splash screen
void displaySplash();

// Establish default text settings and calls 
// appropriate `updateDisplay` function based on setting
void updateDisplay();

// Update display when no game is running
void updateDisplay_NoGame();

// Updates display to show statistics when `gameMode`
// is set to Basic (Static)
void updateDisplay_BasicStatic();

// Updates display to show statistics when `gameMode`
// is set to Basic (Random)
void updateDisplay_BasicRandom();

// Takes `unsigned int time` representing time in milliseconds and
// outputs human-readable time string in the format `HH:MM:SS.FFF`
String formatTime(unsigned int time);

#endif //display_h