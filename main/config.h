#include <Arduino.h>
#include <LittleFS.h>

#include "button.h"
#include "colors.h"
#include "display.h"
#include "fileman.h"
#include "hardware.h"
#include "game.h"
#include "logging.h"
#include "secrets.h"
#include "settings.h"
#include "webpage.h"

#define DEBUG false

#define MDNS_HOSTNAME "crate"