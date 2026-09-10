#include "Arduino.h"

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL9kCNuinW"
#define BLYNK_DEVICE_NAME "Relay Controller"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD

#include "BlynkEdgent.h"

int relaypin = D5;

void setup() {
  Serial.begin(9600);

  pinMode(relaypin, OUTPUT);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V1) {
  int relaystate = param.asInt();
  if (relaystate == 0) {
    digitalWrite(relaypin, LOW);
  } 
  if (relaystate == 1) {
    digitalWrite(relaypin, HIGH);
  }
}