#ifndef colors_h
#define colors_h

#include "Arduino.h"

#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_RAINBOW_RATE 50

extern int brightness;
extern int rainbowRate;

typedef struct {
  double r;       // a fraction between 0 and 1
  double g;       // a fraction between 0 and 1
  double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
  double h;       // angle in degrees
  double s;       // a fraction between 0 and 1
  double v;       // a fraction between 0 and 1
} hsv;

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);

void initColors();
rgb getRainbowRGB();

#endif //colors_h