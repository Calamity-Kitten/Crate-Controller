#include "button.h"

static int buttonPrevState;
static int buttonCurState;

static int debounce = DEBOUNCE_TIME;

void checkButton() {
  buttonPrevState = buttonCurState;
  buttonCurState = digitalRead(BUTTON);

  if (buttonCurState && ! buttonPrevState && millis() > debounce) {
    debounce = millis();
  }
}

void buttonPress() {
  
}