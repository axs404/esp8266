#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
// inclue for I2C library
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

  delay(1000);
}