#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

String msg = "Hello";
int strLength;

void setup() {
  Serial.begin(9600);

  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a msg.
  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(msg);
}

void loop() {
  while (Serial.available() == 0) 
  {  /* Wait for user input */ }
  msg = Serial.readString(); // read the msg from the Serial port
  // strLength = msg.length();
  // if (strLength == 16) {
  Serial.println(msg);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(msg);
  // }
  delay(1000);
}