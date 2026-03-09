#ifndef colors_h
#define colors_h

#include "config.h"

#define PWM_FREQ 500
#define PWM_RESOLUTION 16
#define MAX_DUTY_CYCLE (unsigned int)(pow(2, PWM_RESOLUTION) - 1)

#define DEFAULT_BRIGHTNESS 25 // scale of 0 to 255
#define MINIMUM_BRIGHTNESS 0 // 25 for 8-bit, 20 for 12-bit, 10 for 16-bit
#define MAXIMUM_BRIGHTNESS MAX_DUTY_CYCLE

#define DEFAULT_RAINBOW_RATE 50

#define COLOR_MODE_RAINBOW 0
#define COLOR_MODE_STATIC 1
#define DEFAULT_COLOR_MODE COLOR_MODE_RAINBOW
#define MINIMUM_COLOR_MODE 0
#define MAXIMUM_COLOR_MODE 1
#define DEFAULT_COLOR_RED 245.0 / 255.0
#define DEFAULT_COLOR_GREEN 169.0 / 255.0
#define DEFAULT_COLOR_BLUE 184.0 / 255.0

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
void setButtonLED();
void setButtonLED(rgb buttonColor);
void clearButtonLED();
void setBrightness(unsigned int newBrightness);
unsigned int getBrightness();
unsigned char getColorMode();
void setColorMode(unsigned char newColorMode);
rgb getStaticColor();
void setStaticColor(double newRed, double newGreen, double newBlue);

#endif //colors_h