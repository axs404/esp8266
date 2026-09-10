#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define EEPROM_SIZE 512
#define SSID_MAX_LENGTH 32
#define MAX_SSID_COUNT 10

const char *testPassword = "###########";

String encryptionTypeToStr(uint8_t type) {
  switch (type) {
    case ENC_TYPE_NONE: return "OPEN";
    case ENC_TYPE_WEP: return "WEP";
    case ENC_TYPE_TKIP: return "WPA/TKIP";
    case ENC_TYPE_CCMP: return "WPA2/AES";
    case ENC_TYPE_AUTO: return "AUTO";
    default: return "UNKNOWN";
  }
}

void saveSSIDToEEPROM(String ssid) {
  int addr = 0;
  int count = EEPROM.read(addr);
  if (count >= MAX_SSID_COUNT) return;

  addr = 1 + (count * SSID_MAX_LENGTH);
  for (int i = 0; i < SSID_MAX_LENGTH; i++) {
    if (i < ssid.length())
      EEPROM.write(addr + i, ssid[i]);
    else
      EEPROM.write(addr + i, 0);
  }

  EEPROM.write(0, count + 1);
  EEPROM.commit();
}

void printStoredSSIDs() {
  int count = EEPROM.read(0);
  Serial.printf("Stored SSIDs (%d):\n", count);
  for (int n = 0; n < count; n++) {
    int addr = 1 + (n * SSID_MAX_LENGTH);
    char ssid[SSID_MAX_LENGTH];
    for (int i = 0; i < SSID_MAX_LENGTH; i++) {
      ssid[i] = EEPROM.read(addr + i);
    }
    Serial.println(ssid);
  }
}

void scanAndStoreSSIDs() {
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();
  Serial.printf("Found %d networks:\n", n);

  for (int i = 0; i < n; i++) {
    String ssid = WiFi.SSID(i);
    String bssid = WiFi.BSSIDstr(i);
    int rssi = WiFi.RSSI(i);
    int channel = WiFi.channel(i);
    String enc = encryptionTypeToStr(WiFi.encryptionType(i));

    Serial.printf("%d: %s | BSSID: %s | RSSI: %d | Ch: %d | Enc: %s\n",
                  i + 1, ssid.c_str(), bssid.c_str(), rssi, channel, enc.c_str());

    saveSSIDToEEPROM(ssid);

    // Also display each found network briefly on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Found Network:");
    display.println(ssid);
    display.print("RSSI: ");
    display.println(rssi);
    display.print("Ch: ");
    display.print(channel);
    display.print(" ");
    display.println(enc);
    display.display();
    delay(1000);
  }
}

void connectToStoredSSIDs() {
  int count = EEPROM.read(0);
  for (int n = 0; n < count; n++) {
    int addr = 1 + (n * SSID_MAX_LENGTH);
    char ssid[SSID_MAX_LENGTH];
    for (int i = 0; i < SSID_MAX_LENGTH; i++) {
      ssid[i] = EEPROM.read(addr + i);
    }
    ssid[SSID_MAX_LENGTH - 1] = '\0';

    Serial.printf("Trying to connect to SSID: %s\n", ssid);
    WiFi.begin(ssid, testPassword);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
      delay(500);
      Serial.print(".");
      retries++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
      Serial.printf("Connected to %s\n", ssid);
      Serial.printf("BSSID: %s\n", WiFi.BSSIDstr().c_str());
      Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
      Serial.printf("Subnet: %s\n", WiFi.subnetMask().toString().c_str());
      Serial.printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
      Serial.printf("DNS: %s\n", WiFi.dnsIP().toString().c_str());
      Serial.printf("ESP MAC: %s\n", WiFi.macAddress().c_str());

      // OLED display
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("Connected to:");
      display.println(ssid);
      display.print("BSSID: ");
      display.println(WiFi.BSSIDstr());
      display.print("IP: ");
      display.println(WiFi.localIP());
      display.print("GW: ");
      display.println(WiFi.gatewayIP());
      display.print("DNS: ");
      display.println(WiFi.dnsIP());
      display.display();
      return;
    }
  }
  Serial.println("Could not connect to any stored SSID.");
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;)
      ;
  }
  display.display();
  delay(2000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  scanAndStoreSSIDs();
  printStoredSSIDs();
  connectToStoredSSIDs();
}

void loop() {
}
