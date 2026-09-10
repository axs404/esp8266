#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

void setup() {
  lcd.init(); // initialize the lcd
  //lcd.backlight();
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  //if(sensorValue = 1024){
    //lcd.setCursor(6,1);
    //lcd.print("Max Value");
    //delay(1000);
  //}
  //if(sensorValue != 1024){
    //lcd.setCursor(6,1);
    //lcd.print("         ");
    //delay(1000);
  //}
  // print the results to the Serial Monitor:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SENSOR VALUE = ");
  lcd.setCursor(0,1);
  lcd.print(sensorValue);
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
