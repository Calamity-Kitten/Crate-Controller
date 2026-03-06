#ifndef webpage_h
#define webpage_h

#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "config.h"

#define JSON_SIZE 150

void initWiFi();
void initWebSocket();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void setHandlers();

String processor(const String& var);

void notifyClients();

#endif