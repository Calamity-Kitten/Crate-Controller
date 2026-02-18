#ifndef webpage_h
#define webpage_h

#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>

#include "config.h"

void initWiFi();
void updateWiFi();

void handleRoot();
void handleNotFound();

#endif