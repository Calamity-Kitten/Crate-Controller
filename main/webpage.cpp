#include "webpage.h"

WebServer server(80);

void initWiFi() {
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("\nWiFi connected\nIP address: \n%s\n\n", WiFi.localIP().toString());

  if (!MDNS.begin("crate")) {
    Serial.println("Error setting up mDNS responder!");
    setButtonLED({.r = 1.0, .g = 0.0, .b = 0.0});
    while(1) delay(1000);
  }
  Serial.println("mDNS responder started");

  server.on("/", handleRoot);
  server.serveStatic("/style.css", SPIFFS, "/style.css");
  server.serveStatic("/test_file.html", SPIFFS, "/test_file.html");
  server.onNotFound(handleNotFound);

  server.begin();
}

void updateWiFi() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "Hello, world!");
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}