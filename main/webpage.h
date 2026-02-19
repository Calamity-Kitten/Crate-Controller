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
void handleChangeBrightness(unsigned char newBrightness);
void handleReadBrightness();
void handleRoot();
void handleNotFound();

#endif