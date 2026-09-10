#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();  
 // clear the lcd
  lcd.clear();
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  // clear the lcd
  lcd.clear();
  // set the lcd cursor to the home position
  lcd.setCursor(0,0);
  // print the values read
  lcd.print(sensorValue);
  // check to see if the threshold is less than the value
  if (sensorValue > 100) {
    lcd.setCursor(0, 1);
    lcd.print("Metal");
  }
  else if (sensorValue < 100) {
    lcd.setCursor(0, 1);
    lcd.print("Non-Metal");
  }
  delay(1000);  // delay in between reads for stability
}
