#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27,16,2); 

// Make custom characters:
byte LegsSeparate[] = {
  0b11111,
  0b10101,
  0b11111,
  0b00100,
  0b11111,
  0b00100,
  0b01010,
  0b10001
};
byte LegsTogether[] = {
  0b11111,
  0b10101,
  0b11111,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b00100
};
byte TopLine1[] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte TopLine2[] = {
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte TopLine3[] = {
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte TopLine4[] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte TopLine5[] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};


void setup() {
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  
  lcd.createChar(1, LegsSeparate);
  lcd.createChar(2, LegsTogether);
  lcd.createChar(3, TopLine1);
  lcd.createChar(4, TopLine2);
  lcd.createChar(5, TopLine3);
  lcd.createChar(6, TopLine4);
  lcd.createChar(7, TopLine5);

  // Clear the LCD screen:
  lcd.clear();
  // Print a message to the lcd:
  lcd.print("Arduino Emojis");


  //lcd.home();
 // lcd.setCursor(7,0);
  //lcd.write((byte)0);
}

void loop() { 
  lcd.setCursor(0, 1);
  lcd.write((byte)1);
  
  lcd.setCursor(2, 1);
  lcd.write((byte)2);
  
  lcd.setCursor(4, 1);
  lcd.write((byte)3);
  
  lcd.setCursor(6, 1);
  lcd.write((byte)4);
  
  lcd.setCursor(8, 1);
  lcd.write((byte)5);
  
  lcd.setCursor(10, 1);
  lcd.write((byte)6);
  
  lcd.setCursor(12, 1);
  lcd.write((byte)7);
  
}
