#include "colors.h"

static unsigned int brightness = DEFAULT_BRIGHTNESS;
static int rainbowRate = DEFAULT_RAINBOW_RATE;
static unsigned char colorMode = DEFAULT_COLOR_MODE;
static rgb staticColor = {.r=DEFAULT_COLOR_RED, .g=DEFAULT_COLOR_GREEN, .b=DEFAULT_COLOR_BLUE};

hsv rgb2hsv(rgb in) {
  hsv out;
  double min, max, delta;

  min = in.r < in.g ? in.r : in.g;
  min = min < in.b ? min : in.b;

  max = in.r > in.g ? in.r : in.g;
  max = max > in.b ? max : in.b;

  out.v = max; // v
  delta = max - min;
  if (delta < 0.00001)
  {
    out.s = 0;
    out.h = 0; // undefined, maybe nan?
    return out;
  }
  if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
    out.s = (delta / max); // s
  } else {
    // if max is 0, then r = g = b = 0
    // s = 0, h is undefined
    out.s = 0.0;
    out.h = NAN; // its now undefined
    return out;
  }
  if( in.r >= max ) // > is bogus, just keeps compilor happy
    out.h = ( in.g - in.b ) / delta; // between yellow & magenta
  else
  if( in.g >= max )
    out.h = 2.0 + ( in.b - in.r ) / delta; // between cyan & yellow
  else
    out.h = 4.0 + ( in.r - in.g ) / delta; // between magenta & cyan

  out.h *= 60.0; // degrees

  if( out.h < 0.0 )
    out.h += 360.0;

  return out;
}

rgb hsv2rgb(hsv in) {
  double hh, p, q, t, ff;
  long i;
  rgb out;

  if(in.s <= 0.0) { // < is bogus, just shuts up warnings
    out.r = in.v;
    out.g = in.v;
    out.b = in.v;
    return out;
  }
  hh = in.h;
  if(hh >= 360.0) hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = in.v * (1.0 - in.s);
  q = in.v * (1.0 - (in.s * ff));
  t = in.v * (1.0 - (in.s * (1.0 - ff)));

  switch(i) {
  case 0:
    out.r = in.v;
    out.g = t;
    out.b = p;
    break;
  case 1:
    out.r = q;
    out.g = in.v;
    out.b = p;
    break;
  case 2:
    out.r = p;
    out.g = in.v;
    out.b = t;
    break;

  case 3:
    out.r = p;
    out.g = q;
    out.b = in.v;
    break;
  case 4:
    out.r = t;
    out.g = p;
    out.b = in.v;
    break;
  case 5:
  default:
    out.r = in.v;
    out.g = p;
    out.b = q;
    break;
  }
  return out;
}

rgb getRainbowRGB() {
  double hueValue = (double)((millis() / rainbowRate) % 360);

  hsv currentColorHSV = {.h = (double)hueValue, .s = 1.0, .v = 1.0};
  return hsv2rgb(currentColorHSV);
}

void setButtonLED() {
  if (colorMode == COLOR_MODE_RAINBOW) {
    setButtonLED(getRainbowRGB());
  } else if (colorMode == COLOR_MODE_STATIC) {
    setButtonLED(staticColor);
  }
}

void setButtonLED(rgb buttonColor) {
  constrain(buttonColor.r, 0.0, 1.0);
  constrain(buttonColor.g, 0.0, 1.0);
  constrain(buttonColor.b, 0.0, 1.0);

  ledcWriteChannel(0, (unsigned int)(buttonColor.r * pow(2, brightness)));
  ledcWriteChannel(1, (unsigned int)(buttonColor.g * pow(2, brightness)));
  ledcWriteChannel(2, (unsigned int)(buttonColor.b * pow(2, brightness)));
}

void clearButtonLED() {
    setButtonLED({.r = 0.0, .g = 0.0, .b = 0.0});
}

void setBrightness(unsigned int newBrightness) {
  // No need for sanity checking here since it's included in the setButtonLED function
  Serial.printf("Old: %d, Target: %d ", brightness, newBrightness);
  brightness = newBrightness;
  Serial.printf("New: %d\n", brightness);
}

unsigned int getBrightness() {
  return brightness;
}

unsigned char getColorMode() {
  return colorMode;
}

void setColorMode(unsigned char newColorMode) {
  colorMode = newColorMode;
}

rgb getStaticColor() {
  return staticColor;
}

void setStaticColor(double newRed, double newGreen, double newBlue) {
  staticColor = {.r=newRed, .g=newGreen, .b=newBlue};
}