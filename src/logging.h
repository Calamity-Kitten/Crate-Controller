#ifndef logging_h
#define logging_h

#include <limits.h>

#include "config.h"

#define LOG_SIZE 12*60

// Set `logIndex`, `minTime`, and `maxTime`
void initLog(unsigned int index, unsigned int logMinTime, unsigned int logMaxTime);

// Set `gameLog[i]` to value `v`
void initLog(unsigned int i, unsigned int v);

// Reset all `gameLog` values to `-1`, `logIndex` to `0`, `maxTime` to `0`, and `minTime` to `UINT_MAX`
void resetLog();

// Calls `saveSettings()` to store log (and all settings) to flash
void saveLog();

// Adds new `pressTime` to `gameLog`, updates `logIndex`, `minTime`, and `maxTime`, and saves log to flash
void logPress(unsigned int pressTime);


unsigned int getLog(unsigned int i);
unsigned int getLogMinTime();
unsigned int getLogMaxTime();
unsigned int getLogIndex();

#endif logging_h