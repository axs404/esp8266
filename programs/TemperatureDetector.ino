#include <LiquidCrystal_I2C.h>

// Set the lcd address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "DHT.h"

#define DHTPIN 7     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize the lcd
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();  
  // Begin the serial connection
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  // Initialize the dht sensor
  dht.begin();
  // clear the lcd
  lcd.clear();
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  //if (isnan(h) || isnan(t) || isnan(f)) {
  //  Serial.setCursor(0, 0);
  //  Serial.println("Failed to read! ");
  //return;
  //}

  // Clear any text on the Serial screen 
  lcd.clear();

 // Serial.setCursor(0, 1);
  Serial.print("Humidity: ");
 // Serial.setCursor(10, 1);
  Serial.print(h);
 // Serial.setCursor(12, 1);
  Serial.print("%");
 // Serial.setCursor(0, 2);
  Serial.print("Temperature: ");
 // Serial.setCursor(12, 2);
  Serial.print(t);
 // Serial.setCursor(14, 1);
  Serial.print("°C ");
}