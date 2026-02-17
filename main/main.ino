#include "hardware.h"
#include "colors.h"

void setup() {
  // put your setup code here, to run once:
  initHardware();
  initColors();
}

void loop() {
  // put your main code here, to run repeatedly:
  setButtonLED(getRainbowRGB());
}

void setButtonLED(rgb buttonColor) {
  Serial.printf("R: %3d, G: %3d, B: %3d, V: %3d\n", buttonColor.r, buttonColor.g, buttonColor.b, brightness);
  analogWrite(RED_LED, buttonColor.r * brightness);
  analogWrite(BLUE_LED, buttonColor.g * brightness);
  analogWrite(GREEN_LED, buttonColor.b * brightness);
}