#include <string>
#include "logging.h"

static unsigned int minTime = UINT_MAX;
static unsigned int maxTime = 0;

static unsigned int gameLog[LOG_SIZE];
static unsigned int logIndex = 0;

void initLog(unsigned int index, unsigned int logMinTime, unsigned int logMaxTime) {
  logIndex = index;
  minTime = logMinTime;
  maxTime = logMaxTime;
}

void initLog(unsigned int i, unsigned int v) {
  gameLog[i] = v;
}

// load log file, save min and max
void resetLog() {
  for (int i = 0; i < LOG_SIZE; i++) {
    gameLog[i] = -1;
  }
  minTime = UINT_MAX;
  maxTime = 0;
  logIndex = 0;
}

void saveLog() {
  saveSettings();

  Serial.printf("LogIndex: %d | LogMinTime: %d | LogMaxTime: %d\n",
    logIndex,
    minTime,
    maxTime
  );
  return;
}

void logPress(unsigned int pressTime) {
  gameLog[logIndex] = pressTime;
  logIndex++;

  if (pressTime < minTime) minTime = pressTime;
  if (pressTime > maxTime) maxTime = pressTime;

  saveLog();
}

unsigned int getLog(unsigned int i) {
  return gameLog[i];
}

unsigned int getLogMinTime() {
  return minTime;
}

unsigned int getLogMaxTime() {
  return maxTime;
}

unsigned int getLogIndex() {
  return logIndex;
}