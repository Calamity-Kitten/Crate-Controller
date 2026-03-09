#include "settings.h"

static Preferences preferences;
static unsigned int arr[LOG_SIZE];

void initSettings() {
  preferences.begin(PREFERENCES_NAMESPACE, PREFERENCES_MODE_RW);
  loadSettings();
}

void loadSettings() {
  setBrightness(preferences.getUInt("Brightness", DEFAULT_BRIGHTNESS));
  setMinimumTime(preferences.getUInt("MinimumTime", DEFAULT_MINIMUM_TIME));
  setMaximumTime(preferences.getUInt("MaximumTime", DEFAULT_MAXIMUM_TIME));
  setStaticTime(preferences.getUInt("StaticTime", DEFAULT_STATIC_TIME));
  setColorMode(preferences.getUChar("ColorMode", DEFAULT_COLOR_MODE));
  setGameMode(preferences.getUChar("GameMode", DEFAULT_GAME_MODE)); // This needs to be at the end or it runs on defaults rather than saved value
  initLog(
    preferences.getUInt("LogIndex", 0),
    preferences.getUInt("LogMinTime", UINT_MAX),
    preferences.getUInt("LogMaxTime", 0)
  );

  preferences.getBytes("GameLog", &arr, sizeof(arr));
  for (int i = 0; i < LOG_SIZE; i++) {
    initLog(i, arr[i]);
  }


  Serial.printf(
    "Brightness: %d | GameMode: %d | MinTime: %d | MaxTime: %d | StaticTime: %d | LogIndex: %d | LogMinTime: %d | LogMaxTime: %d | ColorMode: %d | ",
    preferences.getUInt("Brightness", DEFAULT_BRIGHTNESS),
    preferences.getUChar("GameMode", DEFAULT_GAME_MODE),
    preferences.getUInt("MinimumTime", DEFAULT_MINIMUM_TIME),
    preferences.getUInt("MaximumTime", DEFAULT_MAXIMUM_TIME),
    preferences.getUInt("StaticTime", DEFAULT_STATIC_TIME),
    preferences.getUInt("LogIndex", 0),
    preferences.getUInt("LogMinTime", UINT_MAX),
    preferences.getUInt("LogMaxTime", 0),
    preferences.getUChar("ColorMode", DEFAULT_COLOR_MODE)
  );
  for (int i = 0; i < LOG_SIZE; i++) {
    Serial.printf("%d, ", getLog(i));
  }
  Serial.println();
}

//TODO: Log not saving
void saveSettings() {
  preferences.putUInt("Brightness", getBrightness());
  preferences.putUChar("GameMode", getGameMode());
  preferences.putUInt("MinimumTime", getMinimumTime());
  preferences.putUInt("MaximumTime", getMaximumTime());
  preferences.putUInt("StaticTime", getStaticTime());
  preferences.putUInt("LogIndex", getLogIndex());
  preferences.putUInt("LogMinTime", getLogMinTime());
  preferences.putUInt("LogMaxTime", getLogMaxTime());
  preferences.putUChar("ColorMode", getColorMode());
  
  Serial.print("NewArr: ");
  for (int i = 0; i < LOG_SIZE; i++) {
    arr[i] = getLog(i);
    Serial.printf("%d:%d, ", i, arr[i]);
  }
  Serial.println();
  preferences.putBytes("GameLog", (byte*)(&arr), sizeof(arr));

  loadSettings();
}