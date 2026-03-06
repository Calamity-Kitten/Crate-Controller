#include "logging.h"

static unsigned int minTime = UINT_MAX;
static unsigned int maxTime = 0;

void logPress(unsigned int pressTime) {
  appendFile(LittleFS, LOG_NAME, (String(pressTime) + "\n").c_str());
}