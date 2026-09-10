#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiClient client;

// WiFi parameters to be configured
const char* ssid = "########"; // Write here your router's username
const char* password = "##########"; // Write here your router's password

void setup()
{ 
  Serial.begin(115200);
  delay(15);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Serial.println(F("\nESP8266 WiFi scan example"));

  display.setTextWrap(false);
  display.clearDisplay();

  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);

    // clear the OLED display
  display.clearDisplay();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    // Display Text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,8);
    display.println("Connecting...");
    display.display();
  }
  if (WiFi.status() == WL_CONNECTED) {
    // clear the OLED display
    display.clearDisplay();
    // Display Text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Connected to");
    display.setCursor(0,18);
    display.println(ssid);
    display.setCursor(0,36);
    display.println(password);
    display.setCursor(0,54);
    display.println(WiFi.localIP());
    display.display();
  }
}

void loop() 
{
  // wait a bit before scanning again
  // delay(30000);
}