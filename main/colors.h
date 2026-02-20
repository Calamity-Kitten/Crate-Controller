#ifndef colors_h
#define colors_h

#include <Arduino.h>
#include "config.h"

#define DEFAULT_BRIGHTNESS 25 // scale of 0 to 255
#define DEFAULT_RAINBOW_RATE 50

typedef struct {
  double r; // a fraction between 0 and 1
  double g; // a fraction between 0 and 1
  double b; // a fraction between 0 and 1
} rgb;

typedef struct {
  double h; // angle in degrees
  double s; // a fraction between 0 and 1
  double v; // a fraction between 0 and 1
} hsv;

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);

rgb getRainbowRGB();
void setButtonLED(rgb buttonColor);
void clearButtonLED();
void setBrightness(unsigned char newBrightness);
unsigned char getBrightness();

#endif //colors_h