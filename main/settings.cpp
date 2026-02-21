#include "settings.h"

static Preferences preferences;

void initSettings() {
  preferences.begin(PREFERENCES_NAMESPACE, PREFERENCES_MODE_RW);
}

void loadSettings() {
  setBrightness(preferences.getUChar("Brightness", DEFAULT_BRIGHTNESS));

  setGameMode(preferences.getUChar("GameMode", DEFAULT_GAME_MODE));
  setMinimumTime(preferences.getUInt("MinimumTime", DEFAULT_MINIMUM_TIME));
  setMaximumTime(preferences.getUInt("MaximumTime", DEFAULT_MAXIMUM_TIME));
  setStaticTime(preferences.getUInt("StaticTime", DEFAULT_STATIC_TIME));
}

void saveSettings() {
  preferences.putUChar("Brightness", getBrightness());

  preferences.putUChar("GameMode", getGameMode());
  preferences.putUInt("MinimumTime", getMinimumTime());
  preferences.putUInt("MaximumTime", getMaximumTime());
  preferences.putUInt("StaticTime", getStaticTime());
}