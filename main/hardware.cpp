#include "hardware.h"

void initHardware() {
  // Initialize outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  // Define outputs
  digitalWrite(RED_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Initialize Inputs
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(KEYSWITCH, INPUT_PULLUP);
  pinMode(TOGGLESWITCH, INPUT_PULLUP);
}

void toggleOutput(char outputPin) {
  digitalWrite(outputPin, !digitalRead(outputPin));
}