#include "button.h"

static int buttonPrevState;
static int buttonCurState;

static int debounce = DEBOUNCE_TIME;

bool checkButton() {
  buttonPrevState = buttonCurState;
  buttonCurState = digitalRead(BUTTON);

  bool changed = (buttonCurState != buttonPrevState);
  bool debounced = millis() <= debounce;
  if (changed) {
    debounce = millis() + DEBOUNCE_TIME;
    if (debounced) return false;
    else if (buttonCurState==BUTTON_PRESSED) {
      if (DEBUG) Serial.printf("Button Pressed! %d\n", millis());
      return true;
    }
  }
  return false;
}