/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL3VjAeYKk6"
#define BLYNK_TEMPLATE_NAME "Blynk RGB Led"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

const int redPin = D5;
const int greenPin = D6;
const int bluePin = D7;
int aredValue;
int agreenValue;
int ablueValue;
int mredValue;
int mgreenValue;
int mblueValue;
#define delayTime 250

int mode = 1;

void redLight();
void greenLight();
void blueLight();

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, HIGH);

  BlynkEdgent.begin();

  Serial.print("Setup Mode = ");
  Serial.println(mode);
  if (mode == 1) {
    redLight();
    greenLight();
    blueLight();
  }
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V0) {
  mredValue = param.asInt();
  // Serial.print("Initial Mode = ");
  // Serial.println(mode);
  if (mode == 0) {
    analogWrite(redPin, 255 - mredValue);
  }
}

BLYNK_WRITE(V1) {
  mgreenValue = param.asInt();
  // Serial.print("Initial Mode = ");
  // Serial.println(mode);
  if (mode == 0) {
    analogWrite(greenPin, 255 - mgreenValue);
  }
}

BLYNK_WRITE(V2) {
  mblueValue = param.asInt();
  // Serial.print("Initial Mode = ");
  // Serial.println(mode);
  if (mode == 0) {
    analogWrite(bluePin, 255 - mblueValue);
  }
}

BLYNK_WRITE(V3) {
  mode = param.asInt();
  Serial.print("Current Mode = ");
  Serial.println(mode);
  while (mode == 1) {
    if (mode == 1) {
      redLight();
      greenLight();
      blueLight();
    }
    mode = param.asInt();
    Serial.print("Loop Mode = ");
    Serial.println(mode);
  } 
}

void redLight() {
  aredValue = 255;
  ablueValue = 0;
  agreenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    agreenValue += 1;
    aredValue -= 1;
    analogWrite(greenPin, 255 - agreenValue);
    analogWrite(redPin, 255 - aredValue);

    delay(delayTime);
  }
}

void greenLight() {
  aredValue = 0;
  ablueValue = 0;
  agreenValue = 255;
  for (int i = 0; i < 255; i += 1) {
    ablueValue += 1;
    agreenValue -= 1;
    analogWrite(bluePin, 255 - ablueValue);
    analogWrite(greenPin, 255 - agreenValue);

    delay(delayTime);
  }
}

void blueLight() {
  aredValue = 0;
  ablueValue = 255;
  agreenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    aredValue += 1;
    ablueValue -= 1;
    analogWrite(redPin, 255 - aredValue);
    analogWrite(bluePin, 255 - ablueValue);

    delay(delayTime);
  }
}