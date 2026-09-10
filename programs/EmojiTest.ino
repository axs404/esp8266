#include <LiquidCrystal_I2C>
LiquidCrystal_I2C lcd(0x27,16,2);
byte LegsSeparate[] = {
  0b01110,
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b01010
};
byte LegsTogether[] = {
  0b01110,
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b00100
};
void setup() {
  lcd.init();
  lcd.backlight();

  //create new characters
  lcd.createChar(1, LegsSeparate);
  lcd.createChar(2, LegsTogether);
}

void loop() { 
  lcd.setCursor(0, 1);
  lcd.write((byte)1);
  delay(500);
  lcd.clear();
  
  lcd.setCursor(0, 1);
  lcd.write((byte)2);
  delay(500);
  lcd.clear();  
