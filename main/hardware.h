// Output pins
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 15

// Input pins
#define BUTTON 18
#define KEYSWITCH 14
#define TOGGLESWITCH 27

// Display Config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // -1 = sharing uC reset pin

void initHardware() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(KEYSWITCH, INPUT_PULLUP);
  pinMode(TOGGLESWITCH, INPUT_PULLUP);
}

void toggleOutput(char outputPin) {
  digitalWrite(outputPin, !digitalRead(outputPin));
}