#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte Anar[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B11111
};

byte Anar1[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01110,
  B11111
};

byte Anar2[] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B01110,
  B11111
};

byte Anar3[] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B11111
};

byte Anar4[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B11111
};

byte Anar5[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B11111
};

byte Anar6[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100
};

byte Anar7[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100
};

byte Anar8[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B00100
};

byte Anar9[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Anar10[] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Anar11[] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Anar12[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

//byte Anar13[] = {
//  B01010,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte Anar14[] = {
//  B01010,
//  B10101,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte Anar15[] = {
//  B01010,
//  B10101,
//  B10101,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte Anar16[] = {
//  B01010,
//  B10101,
//  B10101,
//  B10101,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte Anar17[] = {
//  B01010,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte Anar18[] = {
//  B01010,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B00100,
//  B00100
//};
//
//byte Anar19[] = {
//  B01010,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B00100
//};
//
//byte Anar20[] = {
//  B01010,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101,
//  B10101
//};

void setup() {
  lcd.init();
  lcd.backlight();  
  lcd.createChar(1 , Anar);
  lcd.createChar(2 , Anar1);
  lcd.createChar(3 , Anar2);
  lcd.createChar(4 , Anar3);
  lcd.createChar(5 , Anar4);
  lcd.createChar(6 , Anar5);
//  lcd.createChar(7 , Anar6);
//  lcd.createChar(8 , Anar7);
//  lcd.createChar(9 , Anar8);
//  lcd.createChar(10 , Anar9);
//  lcd.createChar(11 , Anar10);
//  lcd.createChar(12 , Anar11);
//  lcd.createChar(13 , Anar12);
//  lcd.createChar(14 , Anar13);
//  lcd.createChar(15 , Anar14);
//  lcd.createChar(16 , Anar15);
//  lcd.createChar(17 , Anar16);
//  lcd.createChar(18 , Anar17);
//  lcd.createChar(19 , Anar18);
//  lcd.createChar(20 , Anar19);
//  lcd.createChar(21 , Anar20);
}

void loop() {
  for(int x = 1; x <= 6; x++) {
     lcd.setCursor(0,1);
     lcd.write(x);
     delay(250);
  }
}
