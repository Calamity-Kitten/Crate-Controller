#ifndef logging_h
#define logging_h

#include <limits.h>

#include "config.h"

#define LOG_SIZE 12*60

void initLog(unsigned int index, unsigned int logMinTime, unsigned int logMaxTime);
void initLog(unsigned int i, unsigned int v);
void resetLog();
void saveLog();

void logPress(unsigned int pressTime);

unsigned int getLog(unsigned int i);
unsigned int getLogMinTime();
unsigned int getLogMaxTime();
unsigned int getLogIndex();

#endif logging_h