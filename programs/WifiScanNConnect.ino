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
    Serial.printf("%d: %s\n", n + 1, ssid);
  }
}

String rssiToQuality(int32_t rssi) {
  if (rssi <= -100) return "0%";
  if (rssi >= -50) return "100%";
  return String(2 * (rssi + 100)) + "%";
}

void saveSSIDToEEPROM(String ssid);
void printStoredSSIDs();

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("ESP8266 WiFi Scanner"));
  display.display();
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("\nDevice Info:");
  Serial.printf("Chip ID: %08X\n", ESP.getChipId());
  Serial.printf("Flash Size: %u bytes\n", ESP.getFlashChipSize());
  Serial.printf("SDK Version: %s\n", ESP.getSdkVersion());
  Serial.printf("MAC Address: %s\n", WiFi.macAddress().c_str());

  printStoredSSIDs();
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Scanning...");
  display.display();

  Serial.println(F("Starting WiFi scan..."));
  int scanResult = WiFi.scanNetworks(false, true);

  if (scanResult <= 0) {
    Serial.printf("No networks found (err=%d)\n", scanResult);
  } else {
    Serial.printf("%d networks found:\n", scanResult);

    for (int i = 0; i < scanResult; i++) {
      String ssid;
      int32_t rssi;
      uint8_t encryptionType;
      uint8_t *bssid;
      int32_t channel;
      bool hidden;

      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);

      String bssidStr = String(bssid[0], HEX) + ":" + String(bssid[1], HEX) + ":" + String(bssid[2], HEX) + ":" + String(bssid[3], HEX) + ":" + String(bssid[4], HEX) + ":" + String(bssid[5], HEX);

      String quality = rssiToQuality(rssi);

      Serial.printf("\nNetwork %d:\n", i + 1);
      Serial.printf("  SSID: %s\n", ssid.c_str());
      Serial.printf("  BSSID: %s\n", bssidStr.c_str());
      Serial.printf("  RSSI: %d dBm (%s)\n", rssi, quality.c_str());
      Serial.printf("  Channel: %d\n", channel);
      Serial.printf("  Hidden: %s\n", hidden ? "Yes" : "No");
      Serial.printf("  Encryption: %d\n", encryptionType);
      Serial.printf("  Band: %s\n", (channel <= 14 ? "2.4 GHz" : "5 GHz"));

      // Show summary on OLED
      display.clearDisplay();
      display.setCursor(0, 0);
      display.printf("SSID: %s\n", ssid.c_str());
      display.printf("RSSI: %d dBm\n", rssi);
      display.printf("Ch: %d\n", channel);
      display.printf("Qual: %s\n", quality.c_str());
      display.display();

      // Attempt connection
      WiFi.begin(ssid.c_str(), testPassword);
      unsigned long startAttempt = millis();
      bool connected = false;

      while (millis() - startAttempt < 10000) {
        if (WiFi.status() == WL_CONNECTED) {
          connected = true;
          break;
        }
        delay(500);
      }

      if (connected) {
        Serial.printf("✅ SUCCESS: Connected to %s (%s)\n", ssid.c_str(), WiFi.localIP().toString().c_str());
        saveSSIDToEEPROM(ssid);
        display.setCursor(0, 40);
        display.printf("OK: %s\n", WiFi.localIP().toString().c_str());
        display.display();
        WiFi.disconnect();
      } else {
        Serial.printf("❌ FAILED: Could not connect to %s\n", ssid.c_str());
        display.setCursor(0, 40);
        display.println("FAIL");
        display.display();
      }

      delay(2000);
    }
  }

  Serial.println(F("\nScan + connect attempts complete. Waiting 30s...\n"));
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Cycle complete");
  display.display();

  delay(30000);
}
