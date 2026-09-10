#include "Arduino.h"

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLT3hTvMD0"
#define BLYNK_DEVICE_NAME "Led Controller"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD

#include "BlynkEdgent.h"

int led1pin = D5;
int led2pin = D6;

void setup() {
  Serial.begin(9600);

  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V1) {
  int led1val = param.asInt();
  analogWrite(led1pin, led1val);
}

BLYNK_WRITE(V2) {
  int led2val = param.asInt();
  analogWrite(led2pin, led2val);
}