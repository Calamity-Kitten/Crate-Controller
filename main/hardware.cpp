#include "hardware.h"

void initHardware() {
  // Initialize outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  // Define outputs
  digitalWrite(RED_LED, LED_OFF);
  digitalWrite(RED_LED, LED_OFF);
  digitalWrite(RED_LED, LED_OFF);

  // Initialize Inputs
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(KEYSWITCH, INPUT_PULLUP);
  pinMode(TOGGLESWITCH, INPUT_PULLUP);

  Serial.begin(115200);
  if (DEBUG) {
    Serial.println("");
    Serial.println("Hardware config complete");
    Serial.printf("Reset reason: ");
    verbose_print_reset_reason(esp_reset_reason());
  }
}

void toggleOutput(char outputPin) {
  digitalWrite(outputPin, !digitalRead(outputPin));
}

void verbose_print_reset_reason(int reason) {
  switch ( reason)
  {
    case 1  : Serial.println ("Vbat power on reset");break;
    case 3  : Serial.println ("Software reset digital core");break;
    case 4  : Serial.println ("Legacy watch dog reset digital core");break;
    case 5  : Serial.println ("Deep Sleep reset digital core");break;
    case 6  : Serial.println ("Reset by SLC module, reset digital core");break;
    case 7  : Serial.println ("Timer Group0 Watch dog reset digital core");break;
    case 8  : Serial.println ("Timer Group1 Watch dog reset digital core");break;
    case 9  : Serial.println ("RTC Watch dog Reset digital core");break;
    case 10 : Serial.println ("Instrusion tested to reset CPU");break;
    case 11 : Serial.println ("Time Group reset CPU");break;
    case 12 : Serial.println ("Software reset CPU");break;
    case 13 : Serial.println ("RTC Watch dog Reset CPU");break;
    case 14 : Serial.println ("for APP CPU, reseted by PRO CPU");break;
    case 15 : Serial.println ("Reset when the vdd voltage is not stable");break;
    case 16 : Serial.println ("RTC Watch dog reset digital core and rtc module");break;
    default : Serial.println ("NO_MEAN");
  }
}