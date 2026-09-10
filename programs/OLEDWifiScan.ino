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
const char* password = "##########"; // Write your router's password here

int retries = 0;
String ssid;
int32_t rssi;
uint8_t encryptionType;
uint8_t *bssid;
int32_t channel;
bool hidden;
int scanResult;

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
  // clear the OLED display
  display.clearDisplay();

  // Serial.println(F("\nESP8266 WiFi scan example"));

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);

  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);

  // Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
}

void loop()
{
  // Print unsorted scan results
  for (int8_t i = 0; i < scanResult; i++) {
    retries = 0;

    WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
    // Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %-11s %3S %s\n"), i, channel, bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5], rssi, (encryptionType == ENC_TYPE_NONE) ? ' ' : '*', hidden ? 'H' : 'V', phyMode.c_str(), wps, ssid.c_str());
    
    WiFi.begin(ssid, password);
    while ((WiFi.status() != WL_CONNECTED) && (retries <= 15)) {
      // clear the OLED display
      display.clearDisplay();      
      // Display Text
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Connecting to");
      display.setCursor(0,18);
      display.println(ssid);
      display.setCursor(0,36);
      display.println("Retries: ");
      display.setCursor(0,54);
      display.println(retries);
      display.display();
      // increase the number of retries
      retries++;
      delay(1000);
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
      delay(5000);
    }
    yield();
  }

  // Wait a bit before scanning again
  delay(20000);
}