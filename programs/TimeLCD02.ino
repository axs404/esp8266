#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
// include for I2C library
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid     = "########";
const char *password = "##########";

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800);

String dayOfTheWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(){
  Serial.begin(115200);

  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.noBacklight();  
  // clear the lcd screen
  lcd.clear();

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
  
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print(timeClient.getFormattedTime());

  int day = timeClient.getDay();
  if (day == 1) {
    lcd.setCursor(0, 0);
    lcd.print("En,So,La-1,Ga,Ga");
    lcd.setCursor(0, 1);
    lcd.print("Che,La-2,A.I,Mat");
  }
  if (day == 2) {
    lcd.setCursor(0, 0);
    lcd.print("So,En,Mat,Bio,En");
    lcd.setCursor(0, 1);
    lcd.print("So,Phy,Math,La-1");
  }
  if (day == 3) {
    lcd.setCursor(0, 0);
    lcd.print("En,Ga,So,Mat,Che");
    lcd.setCursor(0, 1);
    lcd.print("En,AC/Lib,La-1,B");
  }
  if (day == 4) {
    lcd.setCursor(0, 0);
    lcd.print("IHC,E,La-1,So,Ma");
    lcd.setCursor(0, 1);
    lcd.print("Bio,La-2,F.L,Phy");
  }
  if (day == 5) {
    lcd.setCursor(0, 0);
    lcd.print("E,mAc,La-1,Ch,So");
    lcd.setCursor(0, 1);
    lcd.print("So,m,M/D,La-3,Ph");
  }
  Serial.println(dayOfTheWeek[day]);
  
  Serial.println("Entering sleep mode");

  WiFi.forceSleepBegin();

  Serial.println("Entered sleep mode");

  delay(3600000);

  WiFi.forceSleepWake();
}