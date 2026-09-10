#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // -- creating LCD instance
        
int sensorPin = A0;

void setup(){
  // -- initializing the LCD
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Voltage Reader"); 
  delay(1000);
}

void loop()
{
  int inputValue = analogRead(sensorPin);
  float voltage = inputValue * (5.0 / 1023.0);
  lcd.setCursor (0,0); //
  lcd.print("Voltage = "); 
  lcd.setCursor (10,0); //
  lcd.print(voltage); // print 
  delay(100);
}
