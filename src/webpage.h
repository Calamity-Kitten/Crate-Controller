#ifndef webpage_h
#define webpage_h

#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "config.h"

#define JSON_SIZE 400

// Initialize WiFi & LittleFS, start server & websocket, establish handlers
void initWiFi();

// Set up websocket and handler
void initWebSocket();

// Send websocket update and call `notifyClients()`
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

// Respond to websocket events
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

// Setup static handlers
void setHandlers();

// Preprocess HTML (replace vars with live data) before issuing to the client
String processor(const String& var);

// Send updated data to all connected clients
void notifyClients();

#endif