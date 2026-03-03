#ifndef webpage_h
#define webpage_h

#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config.h"

void initWiFi();

void setHandlers();


#endif