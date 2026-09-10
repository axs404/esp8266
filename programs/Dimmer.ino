#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x3F for a 16 chars and 2 line display
const int ledPin = 5;      // the pin that the LED is attached to

void setup() {
  lcd.init(); // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  //lcd.backlight();
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);
}
int brightness;

void loop() {

  // check if data has been sent from the computer:
    while (Serial.available()) {
      brightness = Serial.parseInt(); 
      if (brightness > 0){ 
      analogWrite(ledPin, brightness); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LED STATE = ");
      lcd.setCursor(12,0);
      lcd.print(brightness);
      delay(100);
      }     
    }
}
