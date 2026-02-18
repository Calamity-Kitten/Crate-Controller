#include "colors.h"

// Source - https://stackoverflow.com/a/6930407
// Posted by David Hoerl, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-07, License - CC BY-SA 3.0

static int brightness = DEFAULT_BRIGHTNESS;
static int rainbowRate = DEFAULT_RAINBOW_RATE;

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

// TODO: Load saved preferences
void initColors() {
  
}

rgb getRainbowRGB() {
  double hueValue = (double)((millis() / rainbowRate) % 360);

  hsv currentColorHSV = {.h = (double)hueValue, .s = 1.0, .v = 1.0};
  return hsv2rgb(currentColorHSV);
}

void setButtonLED(rgb buttonColor) {
  analogWrite(RED_LED, buttonColor.r * brightness);
  analogWrite(BLUE_LED, buttonColor.g * brightness);
  analogWrite(GREEN_LED, buttonColor.b * brightness);
}

void clearButtonLED() {
    setButtonLED({.r = 0.0, .g = 0.0, .b = 0.0});
}