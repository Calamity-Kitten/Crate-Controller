#ifndef settings_h
#define settings_h

#include <Preferences.h>

#include "config.h"

#define PREFERENCES_MODE_R true
#define PREFERENCES_MODE_RW false

#define PREFERENCES_NAMESPACE "crate"

void initSettings();

void loadSettings();
void saveSettings();

#endif // settings_h