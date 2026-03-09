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
    } else if (strcmp(kv.key().c_str(), "ColorMode") == 0) {
      setColorMode(constrain(kv.value(), MINIMUM_COLOR_MODE, MAXIMUM_COLOR_MODE));
    } else if (strcmp(kv.key().c_str(), "Color") == 0) {
      setStaticColor(
        constrain((double)kv.value()[0] / 255.0, 0.0, 1.0),
        constrain((double)kv.value()[1] / 255.0, 0.0, 1.0),
        constrain((double)kv.value()[2] / 255.0, 0.0, 1.0)
      );
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
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/report.html", String(), false, processor);
  });
  server.on("^\\/Settings\\/?$", HTTP_GET, [] (AsyncWebServerRequest *request) {
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
  server.on("/report.js", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/report.js");
  });
  
}

String processor(const String& var) {
  if(var == "MINIMUM_BRIGHTNESS") {
    return String(MINIMUM_BRIGHTNESS);
  } else if (var == "MAXIMUM_BRIGHTNESS") {
    return String(MAXIMUM_BRIGHTNESS);
  } else if (var == "BRIGHTNESS") {
    return String(getBrightness());
  } else if(var == "MINIMUM_TIME_MIN") {
    return String(MINIMUM_TIME_MIN / (60 * 1000));
  } else if (var == "MINIMUM_TIME_MAX") {
    return String(MINIMUM_TIME_MAX / (60 * 1000));
  } else if (var == "MINIMUM_TIME") {
    return String(getMinimumTime() / (60 * 1000));
  } else if(var == "MAXIMUM_TIME_MIN") {
    return String(MAXIMUM_TIME_MIN / (60 * 1000));
  } else if (var == "MAXIMUM_TIME_MAX") {
    return String(MAXIMUM_TIME_MAX / (60 * 1000));
  } else if (var == "MAXIMUM_TIME") {
    return String(getMaximumTime() / (60 * 1000));
  } else if(var == "STATIC_TIME_MIN") {
    return String(STATIC_TIME_MIN / (60 * 1000));
  } else if (var == "STATIC_TIME_MAX") {
    return String(STATIC_TIME_MAX / (60 * 1000));
  } else if (var == "STATIC_TIME") {
    return String(getStaticTime() / (60 * 1000));
  } else if (var == "GAMEMODE_0") {
    if (getGameMode() == 0) return "selected";
    else return "";
  } else if (var == "GAMEMODE_1") {
    if (getGameMode() == 1) return "selected";
    else return "";
  } else if (var == "GAMEMODE_2") {
    if (getGameMode() == 2) return "selected";
    else return "";
  } else if (var == "COLORMODE_0") {
    if (getColorMode() == 0) return "selected";
    else return "";
  } else if (var == "COLORMODE_1") {
    if (getColorMode() == 1) return "selected";
    else return "";
  } else if (var == "COLOR_RED") {
    return String(getStaticColor().r * 255);
  } else if (var == "COLOR_GREEN") {
    return String(getStaticColor().g * 255);
  } else if (var == "COLOR_BLUE") {
    return String(getStaticColor().b * 255);
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
  json["ColorMode"] = String(getColorMode());
  JsonArray color = json["Color"].to<JsonArray>();
  color.add(String((int)(getStaticColor().r * 255)));
  color.add(String((int)(getStaticColor().g * 255)));
  color.add(String((int)(getStaticColor().b * 255)));

  char data[JSON_SIZE];
  size_t len = serializeJson(json, data);
  Serial.println(data);
  ws.textAll(data, len);
}