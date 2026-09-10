#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Custom characters byte arrays
byte customchar[8] = {B00000, B01010, B00000, B00000, B00000, B00000, B11111,};
byte a[8] = {B00000, B01010, B00100, B00100, B00000, B01110, B10001,};
byte s[8] = {B00100, B01010, B10001, B10001, B01010, B00100,};
byte s1[8] = {B01110, B01010, B11111, B11011, B11111, B01010, B01110,};
byte s2[8] = {B01010, B00100, B00100, B01010, B10001, B00100, B10001,};
byte s3[8] = {B00100, B01010, B11111, B01010, B10101, B11011, B10001,};
byte s4[8] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F,};
byte s5[8] = {B11111, B11101, B11011, B11101, B11111, B10000, B10000, B10000,};
byte Heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte Skull[] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};

byte L[] = {
  B00000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01110,
  B00000
};

byte Smily[] = {
  B11111,
  B10101,
  B01010,
  B10101,
  B10101,
  B01010,
  B10101,
  B11011
};

byte Oh[] = {
  B11111,
  B10001,
  B10001,
  B11111,
  B00000,
  B10001,
  B11111,
  B10001
};

//Custom characters byte arrays

void setup()
{
  lcd.init();
  //lcd.backlight();
  lcd.clear();       //Clear lcd display screen

  lcd.createChar(1 , customchar);   //Creating custom characters in CG-RAM
  lcd.createChar(2 , a);
  lcd.createChar(3 , s);
  lcd.createChar(4 , s1);
  lcd.createChar(5 , s2);
  lcd.createChar(6 , s3);
  lcd.createChar(7 , s4);
  lcd.createChar(8 , s5); //Creating custom characters in CG-RAM
  lcd.createChar(9 , Heart);
  lcd.createChar(10 , Skull);
  lcd.createChar(11, L);
  lcd.createChar(12, Smily);
  lcd.createChar(13, Oh);
}
void loop()
{
  int rand, i;
  lcd.setCursor(0 , 0);           //Place lcd cursor on first row and first coulomb of 16x2 lcd
  lcd.print("Arduino Emojis");  //Display this test on first row on 16x2 lcd
  lcd.setCursor(0 , 1);           //Place lcd cursor on second row of 16x2 lcd first coulomb

  for (rand = 0; rand < 13; rand++) { //For loop will display custom characters one by one
    i = random(13);
    lcd.setCursor(i , 1);
    lcd.write(i);                 //-->>>PRINTING/DISPLAYING CUSTOM CHARACTERS
    delay(500);
  }
  lcd.clear();                      //Clear lcd and start again
}
