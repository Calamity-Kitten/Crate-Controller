#ifndef colors_h
#define colors_h

#include "config.h"

#define PWM_FREQ 500
#define PWM_RESOLUTION 16
#define MAX_DUTY_CYCLE (unsigned int)(pow(2, PWM_RESOLUTION) - 1)

#define MINIMUM_BRIGHTNESS 5 // 25 for 8-bit, 20 for 12-bit, 10 for 16-bit
#define MAXIMUM_BRIGHTNESS PWM_RESOLUTION
#define DEFAULT_BRIGHTNESS 10

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

// Takes `rgb` input, outputs `hsv` equivalent
// Source - https://stackoverflow.com/a/6930407
// Posted by David Hoerl, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-07, License - CC BY-SA 3.0
hsv rgb2hsv(rgb in);

// Takes `hsv` input, outputs `rgb` equivalent
// Source - https://stackoverflow.com/a/6930407
// Posted by David Hoerl, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-07, License - CC BY-SA 3.0
rgb hsv2rgb(hsv in);

// Returns `rgb` containing current RGB color for button LED ring
rgb getRainbowRGB();

// Sets button LED based on `colorMode` setting
void setButtonLED();

// Sets button LED ring to `buttonColor`
void setButtonLED(rgb buttonColor);

// Turns off button LED ring
void clearButtonLED();


void setBrightness(unsigned int newBrightness);
unsigned int getBrightness();
unsigned char getColorMode();
void setColorMode(unsigned char newColorMode);
rgb getStaticColor();
void setStaticColor(double newRed, double newGreen, double newBlue);

#endif //colors_h