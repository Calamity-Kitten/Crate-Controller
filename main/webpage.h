#ifndef webpage_h
#define webpage_h

#include <Arduino.h>
#include <ESPmDNS.h>
#include <LittleFS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <uri/UriRegex.h>

#include "config.h"

void initWiFi();
void updateWiFi();

void setHandlers();

void handleGetBrightness();
void handleSetBrightness(unsigned char newBrightness);
void handleGetMaximumTime();
void handleSetMaximumTime(unsigned int newMaximumTime);
void handleGetMinimumTime();
void handleSetMinimumTime(unsigned int newMinimumTime);

void handleNotFound();

#endif