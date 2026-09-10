#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the blacklight
  lcd.backlight();
  // Clear the LCD
  lcd.clear();
}

// the loop routine runs over and over again forever
void loop() {
  // read the input on analog pin 0
  int SensorValue = analogRead(A0);
  // print out the value you read
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("A0 Value = ");
  lcd.setCursor(12,1);
  lcd.print(SensorValue);
  // delay in between reads for stability
  delay(250);
}
