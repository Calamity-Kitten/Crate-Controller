#include "webpage.h"

WebServer server(80);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(WIFI_SSID, WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (DEBUG) Serial.printf("\nIP address: %s\n\n", WiFi.localIP().toString());

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
  if (DEBUG) listDir(LittleFS, "/", 0);

  setHandlers();

  server.begin();
}

void setHandlers() {
  server.on(UriRegex("\/Brightness\/([0-9]+)\/?$"), HTTP_GET, [&]() {
    unsigned char newBrightness = server.pathArg(0).toInt();
    if (server.pathArg(0).toInt() > 255) newBrightness = 255;
    else if (server.pathArg(0).toInt() < 0) newBrightness = 0;
    handleSetBrightness(server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Brightness change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/Brightness\/?"), handleGetBrightness);

  server.on(UriRegex("\/MaximumTime\/([0-9]+)\/?$"), HTTP_GET, [&]() {
    handleSetMaximumTime(server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Maximum Time change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/MaximumTime\/?"), handleGetMaximumTime);

  server.on(UriRegex("\/MinimumTime\/([0-9]+)\/?$"), HTTP_GET, [&]() {
    handleSetMinimumTime(server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Minimum Time change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/MinimumTime\/?"), handleGetMinimumTime);

  server.on(UriRegex("\/StaticTime\/([0-9]+)\/?$"), HTTP_GET, [&]() {
    handleSetStaticTime(server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Static Time change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/StaticTime\/?"), handleGetStaticTime);

  server.on(UriRegex("\/GameMode\/([0-9]+)\/?$"), HTTP_GET, [&]() {
    handleSetGameMode(server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Game Mode change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/GameMode\/?"), handleGetGameMode);

  server.on(UriRegex("\/SaveSettings\/?"), handleSaveSettings);

  server.serveStatic("/", LittleFS, "/settings.html");
  server.serveStatic("/favicon.ico", LittleFS, "/favicon.ico");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/chart.js", LittleFS, "/chart.js");
  server.serveStatic("/settings.js", LittleFS, "/settings.js");
  
  server.onNotFound(handleNotFound);
}

void handleGetBrightness() {
  server.send(200, "text/plain", String(getBrightness()));
}

void handleSetBrightness(unsigned char newBrightness) {
  if (DEBUG) Serial.println("Brightness change requested: " + String(newBrightness));
  setBrightness(newBrightness);
  handleGetBrightness();
}

void handleGetMaximumTime() {
  server.send(200, "text/plain", String(getMaximumTime()));
}

void handleSetMaximumTime(unsigned int newMaximumTime) {
  if (DEBUG) Serial.println("Maximum Time change requested: " + String(newMaximumTime));
  setMaximumTime(newMaximumTime);
  handleGetMaximumTime();
}

void handleGetMinimumTime() {
  server.send(200, "text/plain", String(getMinimumTime()));
}

void handleSetMinimumTime(unsigned int newMinimumTime) {
  if (DEBUG) Serial.println("Minimum Time change requested: " + String(newMinimumTime));
  setMinimumTime(newMinimumTime);
  handleGetMinimumTime();
}

void handleGetStaticTime() {
  server.send(200, "text/plain", String(getStaticTime()));
}

void handleSetStaticTime(unsigned int newStaticTime) {
  if (DEBUG) Serial.println("Static Time change requested: " + String(newStaticTime));
  setStaticTime(newStaticTime);
  handleGetStaticTime();
}

void handleGetGameMode() {
  server.send(200, "text/plain", String(getGameMode()));
}

void handleSetGameMode(unsigned char newGameMode) {
  if (DEBUG) Serial.println("Game Mode change requested: " + String(newGameMode));
  setGameMode(newGameMode);
  handleGetGameMode();
}

void handleSaveSettings() {
  saveSettings();
  server.send(200, "text/plain", "Saved");
}

void updateWiFi() {
  server.handleClient();
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}