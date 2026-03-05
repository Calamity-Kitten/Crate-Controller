#ifndef display_h
#define display_h

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void initDisplay();

void displaySplash();

void updateDisplay();
void updateDisplay_NoGame();
void updateDisplay_BasicStatic();
void updateDisplay_BasicRandom();

String formatTime(unsigned int time);

#endif //display_h