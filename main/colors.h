#ifndef colors_h
#define colors_h

#include <Arduino.h>
#include "config.h"

#define PWM_FREQ 500
#define PWM_RESOLUTION 16
#define MAX_DUTY_CYCLE (unsigned int)(pow(2, PWM_RESOLUTION) - 1)

#define DEFAULT_BRIGHTNESS 25 // scale of 0 to 255
#define MINIMUM_BRIGHTNESS 0 // 25 for 8-bit, 20 for 12-bit, 10 for 16-bit
#define MAXIMUM_BRIGHTNESS MAX_DUTY_CYCLE

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
void setBrightness(unsigned int newBrightness);
unsigned int getBrightness();

#endif //colors_h