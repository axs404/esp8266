#include "Arduino.h"
#include <Servo.h>

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

Servo myservo;
int pos;

void setup() {
  Serial.begin(9600);

  myservo.attach(2);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V1) {
  int servostate = param.asInt();
  if (servostate == 0) {
    for (pos = 90; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(75);
    }
  }
  if (servostate == 1) {
    for (pos = 180; pos >= 90; pos -= 1) {
      myservo.write(pos);
      delay(3);
    }
  }
}