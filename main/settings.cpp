#include "settings.h"

static Preferences preferences;

void initSettings() {
  preferences.begin(PREFERENCES_NAMESPACE, PREFERENCES_MODE_RW);
  loadSettings();
}

void loadSettings() {
  setBrightness(preferences.getUChar("Brightness", DEFAULT_BRIGHTNESS));
  setMinimumTime(preferences.getUInt("MinimumTime", DEFAULT_MINIMUM_TIME));
  setMaximumTime(preferences.getUInt("MaximumTime", DEFAULT_MAXIMUM_TIME));
  setStaticTime(preferences.getUInt("StaticTime", DEFAULT_STATIC_TIME));
  setGameMode(preferences.getUChar("GameMode", DEFAULT_GAME_MODE)); // This needs to be at the end or it runs on defaults rather than saved value

  if (DEBUG) Serial.printf(
    "Brightness: %d | GameMode: %d | MinTime: %d | MaxTime: %d | StaticTime: %d\n",
    preferences.getUChar("Brightness", DEFAULT_BRIGHTNESS),
    preferences.getUChar("GameMode", DEFAULT_GAME_MODE),
    preferences.getUInt("MinimumTime", DEFAULT_MINIMUM_TIME),
    preferences.getUInt("MaximumTime", DEFAULT_MAXIMUM_TIME),
    preferences.getUInt("StaticTime", DEFAULT_STATIC_TIME)
  );
}

void saveSettings() {
  preferences.putUChar("Brightness", getBrightness());
  preferences.putUChar("GameMode", getGameMode());
  preferences.putUInt("MinimumTime", getMinimumTime());
  preferences.putUInt("MaximumTime", getMaximumTime());
  preferences.putUInt("StaticTime", getStaticTime());

  loadSettings();
}