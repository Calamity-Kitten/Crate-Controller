#ifndef settings_h
#define settings_h

#include <Preferences.h>

#include "config.h"

#define PREFERENCES_MODE_R true
#define PREFERENCES_MODE_RW false

#define PREFERENCES_NAMESPACE "crate"

// Opens `preferences` namespace `PREFERENCES_NAMESPACE` and loads settings from flash
void initSettings();

// Loads all settings (and `gameLog`) from flash
void loadSettings();

// Saves all settings (and `gameLog`) to flash
void saveSettings();

#endif // settings_h