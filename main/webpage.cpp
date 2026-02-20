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

  if (!MDNS.begin("crate")) {
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
  server.on(UriRegex("\/brightness\/([0-9]+)\/?"), HTTP_GET, [&]() {
    handleChangeBrightness((unsigned char)server.pathArg(0).toInt());
    if (DEBUG) Serial.printf(" - Brightness change complete: %s\n\n", String(server.pathArg(0).toInt()));
  });
  server.on(UriRegex("\/brightness\/?"), HTTP_GET, [&]() {
    handleReadBrightness();
  });

  server.serveStatic("/", LittleFS, "/settings.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/settings.js", LittleFS, "/settings.js");
  
  server.onNotFound(handleNotFound);
}

void handleChangeBrightness(unsigned char newBrightness) {
  Serial.println("Brightness change requested: " + String(newBrightness));
  setBrightness(newBrightness);
  handleReadBrightness();
}

void handleReadBrightness() {
  server.send(200, "text/plain", String(getBrightness()));
}

void updateWiFi() {
  server.handleClient();
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}