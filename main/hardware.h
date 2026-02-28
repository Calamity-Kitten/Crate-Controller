#ifndef hardware_h
#define hardware_h

#include <Arduino.h>
#include "config.h"

// Output pins
#define RED_LED 32
#define GREEN_LED 33
#define BLUE_LED 25

#define LED_OFF LOW
#define LED_ON HIGH

// Input pins
#define BUTTON 4
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

#define KEYSWITCH 18
#define TOGGLESWITCH 19
#define ADC_PIN 34

// Display Config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // -1 = sharing uC reset pin

void initHardware();

void toggleOutput(char outputPin);
void verbose_print_reset_reason(int reason);

#endif // hardware_h