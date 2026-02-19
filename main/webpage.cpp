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

  if (!LittleFS.begin(true)) {
    Serial.println("Error mounting LittleFS");
    setButtonLED({.r = 1.0, .g = 0.0, .b = 0.0});
    while(1) delay(1000);
  }
  listDir(LittleFS, "/", 0);

  setHandlers();

  server.begin();
}

void setHandlers() {
  server.on(UriRegex("/brightness/([0-9]+)"), HTTP_GET, [&]() {
    handleChangeBrightness((unsigned char)server.pathArg(0).toInt());
  });
  server.on(UriRegex("/brightness(/?)"), HTTP_GET, [&]() {
    handleReadBrightness();
  });

  server.on(UriRegex("/home/([0-9]+)/second"), HTTP_GET, [&]() {
    server.send(200, "text/plain", "Hello from second! URL arg: " + server.pathArg(0));
  });

  server.on("/", handleRoot);
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/test_file.html", LittleFS, "/test_file.html");
  server.serveStatic("/index.html", LittleFS, "/index.html");
  
  server.onNotFound(handleNotFound);
}

void handleChangeBrightness(unsigned char newBrightness) {
  Serial.println("Brightness change requested");
  setBrightness(newBrightness);
  handleReadBrightness();
}

void handleReadBrightness() {
  server.send(200, "text/plain", String(getBrightness()));
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