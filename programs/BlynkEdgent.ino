
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLegqxuBP5"
#define BLYNK_DEVICE_NAME "Blynk Car"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

int en1 = D1;
int en2 = D2;
int in1 = D5;
int in2 = D6;
int in3 = D7;
int in4 = D8;
int motorspeed = 900;

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V1) {
  int forward = param.asInt();
  if (forward == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (forward == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V2) {
  int reverse = param.asInt();
  if (reverse == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (reverse == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

BLYNK_WRITE(V3) {
  int left = param.asInt();
  if (left == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  if (left == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V4) {
  int right = param.asInt();
  if (right == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (right == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}