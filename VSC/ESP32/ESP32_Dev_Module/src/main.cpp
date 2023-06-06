#include <Arduino.h>
#include "LittleFS.h"
#include <DNSServer.h>
#ifdef ESP32
#include "WiFi.h"
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"

const char* ssid = "KT_GiGA_2G_Wave2_1205";
const char* pass = "8ec4hkx000";

const char* ssid_AP = "ESP32C3-WiFiManager";
const char* pass_AP = "12345678"; // 최소 8자리

//WiFiServer myServer(80);
AsyncWebServer myServer(80);
// AsyncEventSource events("/events");

void setup() {
  Serial.begin(115200);
  Serial.println("Start ESP32");
  
  if(!LittleFS.begin(true))
  {
      Serial.println("LittleFS Mount Failed");
      return;
  }
  Serial.println("LittleFS Mounted");
  // // KT 공유기 172.30.1.254
  IPAddress ip (172, 30, 1, 40);
  IPAddress gateway (172, 30, 1, 254);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid_AP, pass_AP);
  //WiFi.softAP(ssid_AP);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.print(F("WiFi Connected -> IP : "));
  Serial.println(WiFi.localIP());

  myServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(LittleFS, "/index.html", "text/html");
  });

  // css, js 파일 사용
  myServer.serveStatic("/", LittleFS, "/");
  
  
  myServer.begin();
}

void loop() {
 
}