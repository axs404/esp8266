#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte EmptyTank[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte LowLvlAlertLeft[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111
};

byte LowLvlAlertRight[] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111
};

byte WaterLevel10[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte WaterLevel20[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};

byte WaterLevel30[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

byte WaterLevel40[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte WaterLevel50[] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte WaterLevel60[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte WaterLevel70[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte WaterLevel80[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};

byte WaterLevel90[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte WaterLevel100[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};

void setup() {
  // initialize the LCD
  lcd.init();
  // Turn on the blacklight and print a message.
  lcd.backlight();  
  lcd.clear();

  lcd.createChar(0, EmptyTank);
  lcd.createChar(1, LowLvlAlertLeft);
  lcd.createChar(2, LowLvlAlertRight);
  lcd.createChar(3, WaterLevel10);
  lcd.createChar(4, WaterLevel20);
  lcd.createChar(5, WaterLevel30);
  lcd.createChar(6, WaterLevel40);
  lcd.createChar(7, WaterLevel50);
  lcd.createChar(8, WaterLevel60);
  lcd.createChar(9, WaterLevel70);
  lcd.createChar(10, WaterLevel80);
  lcd.createChar(11, WaterLevel90);
  lcd.createChar(12, WaterLevel100);
}

void loop() {
  lcd.clear();
  lcd.setCursor()
}
