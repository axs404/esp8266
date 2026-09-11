#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "######"
#define STAPSK "##########"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int redPin = D5;
const int greenPin = D6;
const int bluePin = D7;
int redValue;
int greenValue;
int blueValue;
#define delayTime 250

void lightControl();

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, HIGH);

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  lightControl();
}

void lightControl() {
  int redValue = 255;
  int blueValue = 0;
  int greenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    greenValue += 1;
    redValue -= 1;
    analogWrite(greenPin, 255 - greenValue);
    analogWrite(redPin, 255 - redValue);

    delay(delayTime);
  }

  redValue = 0;
  blueValue = 0;
  greenValue = 255;
  for (int i = 0; i < 255; i += 1) {
    blueValue += 1;
    greenValue -= 1;
    analogWrite(bluePin, 255 - blueValue);
    analogWrite(greenPin, 255 - greenValue);

    delay(delayTime);
  }

  redValue = 0;
  blueValue = 255;
  greenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    redValue += 1;
    blueValue -= 1;
    analogWrite(redPin, 255 - redValue);
    analogWrite(bluePin, 255 - blueValue);

    delay(delayTime);
  }
}