#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int WIRE1 = 14;
int WIRE2 = 12;
int WIRE3 = 13;
int WIRE4 = 15;
String password = "####";
String enteredpassword = "";
String timesofpassword = "";
void beep();

void setup() {
  lcd.init(); // initialize the lcd
  //lcd.backlight();
  // initialize serial communication:  
  pinMode (WIRE1,INPUT_PULLUP);
  pinMode (WIRE2,INPUT_PULLUP);
  pinMode (WIRE3,INPUT_PULLUP);
  pinMode (WIRE4,INPUT_PULLUP);
  Serial.begin(9600);
   
}

void loop() {
   if (enteredpassword != "") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(enteredpassword);
    Serial.println(enteredpassword);
    delay(100);
   }
    
  if ( enteredpassword.length()==4)
  {

    if (enteredpassword == password)
    {
      beep();
      delay(2500);
      beep();
      delay(2500);
      lcd.setCursor(6,0);
      lcd.print("g_l_on");
      Serial.println("green_led_on");
      delay(2500);
      lcd.setCursor(10,0);
      lcd.print("           ");
      lcd.setCursor(10,0);
      lcd.print("off");
      Serial.println("green_led_off");
      lcd.setCursor(0,1);
      lcd.print("s_l_on");
      Serial.println("servoLed_on");
    }
    else
    {
      
      beep();
      delay(2500);
      beep();
      delay(2500);
      beep();
      delay(2500);
      lcd.setCursor(7,0);
      lcd.print("r_l_on");
      Serial.println("red_led_on");
      delay(2500);
      lcd.setCursor(4,0);
      lcd.print("                ");
      lcd.setCursor(4,0);
      lcd.print("off");
      Serial.println("red_led_off");
      lcd.setCursor(9,0);
      lcd.print("               ");
      lcd.setCursor(9,0);
      lcd.print("off");
      Serial.println("servoLed_off");
    }
  enteredpassword="";
  }

   if (digitalRead(WIRE1)==LOW)
   {
    enteredpassword+="1";
    beep();
   } 
   else if (digitalRead(WIRE2)==LOW)
   {
     enteredpassword+="2";
     beep();
   }
   else if (digitalRead(WIRE3)==LOW)
   {
      enteredpassword+="3";
      beep();
   }
   else if (digitalRead(WIRE4)==LOW)
   {
      enteredpassword+="4";
      beep();
   }
}

void beep(){
  Serial.println("buzzerLed_led_on");
  delay(2500);
  Serial.println("buzzerLed_led_off");
}
