#include "webpage.h"

static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");

void initWiFi() {
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(WIFI_SSID, WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("\nIP address: %s\n\n", WiFi.localIP().toString());

  if (!MDNS.begin(MDNS_HOSTNAME)) {
    Serial.println("Error setting up mDNS responder!");
    setButtonLED({.r = 1.0, .g = 0.0, .b = 0.0});
    while(1) delay(1000);
  }
  if (DEBUG) Serial.println("mDNS responder started");

  if (!LittleFS.begin(true)) {
    Serial.println("Error mounting LittleFS");
    setButtonLED({.r = 1.0, .g = 0.0, .b = 0.0});
    while(1) delay(1000);
  }

  initWebSocket();
  setHandlers();

  server.begin();
}

void updateWifi() {
  ws.cleanupClients();
  notifyClients();
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;

  if (!(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT))
    return;

  StaticJsonDocument<JSON_SIZE> json;
  DeserializationError err = deserializeJson(json, data);
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
    return;
  }


  // TODO: Key not matching in if statements
  for (JsonPair kv : json.as<JsonObject>()) {
    // String keyVal = kv.key().c_str;
    Serial.printf(" - %s:%s\n", kv.key().c_str(), String(kv.value()));
    if (strcmp(kv.key().c_str(), "Brightness") == 0) {
      setBrightness(constrain(kv.value(), MINIMUM_BRIGHTNESS, MAXIMUM_BRIGHTNESS));
    } else if (strcmp(kv.key().c_str(), "MaximumTime") == 0) {
      setMaximumTime(constrain(kv.value(), MAXIMUM_TIME_MIN, MAXIMUM_TIME_MAX) * 60 * 1000);
    } else if (strcmp(kv.key().c_str(), "MinimumTime") == 0) {
      setMinimumTime(constrain(kv.value(), MINIMUM_TIME_MIN, MINIMUM_TIME_MAX) * 60 * 1000);
    } else if (strcmp(kv.key().c_str(), "StaticTime") == 0) {
      setStaticTime(constrain(kv.value(), STATIC_TIME_MIN, STATIC_TIME_MAX) * 60 * 1000);
    } else if (strcmp(kv.key().c_str(), "GameMode") == 0) {
      setGameMode(constrain(kv.value(), MINIMUM_GAME_MODE, MAXIMUM_GAME_MODE));
    }
  }
  Serial.printf(" -- Brightness: %s | MaximumTime: %s\n", String(getBrightness()), String(getMaximumTime() / (60 * 1000)));

  saveSettings();
  
  notifyClients();
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void setHandlers() {
  server.on("^\\/Brightness\\/([0-9]+)\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned char newBrightness = constrain(request->pathArg(0).toInt(), MINIMUM_BRIGHTNESS, MAXIMUM_BRIGHTNESS);
    setBrightness(newBrightness);
    request->send(200, "text/plain", String(getBrightness()));
  });
  server.on("^\\/Brightness\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      request->send(200, "text/plain", String(getBrightness()));
  });

  //TODO: Limit max/min time so max is always higher than min. Possibly with JS on the webpage?
  server.on("^\\/MaximumTime\\/([0-9]+)\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned int newMaximumTime = constrain(request->pathArg(0).toInt(), MAXIMUM_TIME_MIN, MAXIMUM_TIME_MAX);
    setMaximumTime(newMaximumTime);
    request->send(200, "text/plain", String(getMaximumTime()));
  });
  server.on("^\\/MaximumTime\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(getMaximumTime()));
  });

  server.on("^\\/MinimumTime\\/([0-9]+)\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned int newMinimumTime = constrain(request->pathArg(0).toInt(), MINIMUM_TIME_MIN, getMaximumTime());
    setMinimumTime(newMinimumTime);
    request->send(200, "text/plain", String(getMinimumTime()));
  });
  server.on("^\\/MinimumTime\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(getMinimumTime()));
  });

  server.on("^\\/StaticTime\\/([0-9]+)\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned int newStaticTime = constrain(request->pathArg(0).toInt(), STATIC_TIME_MIN, STATIC_TIME_MAX);
    setStaticTime(newStaticTime);
    request->send(200, "text/plain", String(getStaticTime()));
  });
  server.on("^\\/StaticTime\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(getStaticTime()));
  });

  server.on("^\\/GameMode\\/([0-9]+)\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned char newGameMode = constrain(request->pathArg(0).toInt(), MINIMUM_GAME_MODE, MAXIMUM_GAME_MODE);
    setGameMode(newGameMode);
    request->send(200, "text/plain", String(getGameMode()));
  });
  server.on("^\\/GameMode\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(getGameMode()));
  });

  server.on("^\\/SaveSettings\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
    saveSettings();
    request->send(200, "text/plain", "Saved");
  });

  // TODO: Add processor() to send settings live rather than use JS
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/settings.html", String(), false, processor);
  });
  server.on("/favicon.ico", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/favicon.ico");
  });
  server.on("/style.css", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css");
  });
  server.on("/settings.js", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/settings.js");
  });
  
}

String processor(const String& var) {
  if(var == "MINIMUM_BRIGHTNESS") {
    return String(MINIMUM_BRIGHTNESS);
  }
  else if (var == "MAXIMUM_BRIGHTNESS") {
    return String(MAXIMUM_BRIGHTNESS);
  }
  else if (var == "BRIGHTNESS") {
    return String(getBrightness());
  } else if(var == "MINIMUM_TIME_MIN") {
    return String(MINIMUM_TIME_MIN / (60 * 1000));
  }
  else if (var == "MINIMUM_TIME_MAX") {
    return String(MINIMUM_TIME_MAX / (60 * 1000));
  }
  else if (var == "MINIMUM_TIME") {
    return String(getMinimumTime() / (60 * 1000));
  } else if(var == "MAXIMUM_TIME_MIN") {
    return String(MAXIMUM_TIME_MIN / (60 * 1000));
  }
  else if (var == "MAXIMUM_TIME_MAX") {
    return String(MAXIMUM_TIME_MAX / (60 * 1000));
  }
  else if (var == "MAXIMUM_TIME") {
    return String(getMaximumTime() / (60 * 1000));
  } else if(var == "STATIC_TIME_MIN") {
    return String(STATIC_TIME_MIN / (60 * 1000));
  }
  else if (var == "STATIC_TIME_MAX") {
    return String(STATIC_TIME_MAX / (60 * 1000));
  }
  else if (var == "STATIC_TIME") {
    return String(getStaticTime() / (60 * 1000));
  }
  return String();
}

void notifyClients() {
  StaticJsonDocument<JSON_SIZE> json;
  json["Brightness"] = String(getBrightness());
  json["MaximumTime"] = String(getMaximumTime() / (60 * 1000));
  json["MinimumTime"] = String(getMinimumTime() / (60 * 1000));
  json["StaticTime"] = String(getStaticTime() / (60 * 1000));
  json["GameMode"] = String(getGameMode());

  char data[JSON_SIZE];
  size_t len = serializeJson(json, data);
  Serial.println(data);
  ws.textAll(data, len);
}