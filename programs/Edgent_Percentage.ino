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
#define BLYNK_TEMPLATE_ID "TMPL3NHQ3Tl5Z"
#define BLYNK_TEMPLATE_NAME "Blynk Servo"

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
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int num1 = 1000;
int num2 = 1000;
float rawPercent;
float finalPercent;

void setup()
{
  Serial.begin(9600);
  delay(100);

  // initialize the LCD
	lcd.begin();
	// Turn off the blacklight and print a message.
	lcd.backlight();

  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Welcome!");

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V0) {
  num1 = param.asInt();
  float rawPercent = num1 * 100;
  float finalPercent = rawPercent/num2;
  // Serial.print("Number = ");
  // Serial.println(num);
  // Serial.print("Percentage = ");
  // Serial.println(finalPercent);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Number 1: ");
  lcd.setCursor(9, 0);
  lcd.print(num1);
  lcd.setCursor(0, 1);
  lcd.print("Percent : ");
  lcd.setCursor(9, 1);
  lcd.print(finalPercent);
  delay(15);
}

BLYNK_WRITE(V1) {
  num2 = param.asInt();
  float rawPercent = num1 * 100;
  float finalPercent = rawPercent/num2;
  // Serial.print("Number = ");
  // Serial.println(num);
  // Serial.print("Percentage = ");
  // Serial.println(finalPercent);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Number 2: ");
  lcd.setCursor(9, 0);
  lcd.print(num2);
  lcd.setCursor(0, 1);
  lcd.print("Percent : ");
  lcd.setCursor(9, 1);
  lcd.print(finalPercent);
  delay(15);
}