#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "############"
#define STAPSK  "################"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "OTA-LEDS";


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Retrying connection...");
  }
  ArduinoOTA.setHostname(host);
  ArduinoOTA.onError([](ota_error_t error) {
    (void)error;
    ESP.restart();
  });

  /* setup the OTA server */
  ArduinoOTA.begin();
  Serial.println("Ready");

  Serial.println(WiFi.localIP());
  
  // Setup code - BEGIN
  // Setup code - END

}

void loop() {
  ArduinoOTA.handle();

  // Loop code - BEGIN
  // Loop code - END
}
