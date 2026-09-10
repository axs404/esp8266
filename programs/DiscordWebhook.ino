#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <user_interface.h>  // For light sleep

// OLED setup
#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
#define OLED_RESET    -1  // Reset pin (not used for I2C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Replace with your WiFi credentials
const char* ssid = "######";
const char* password = "##########";

// Discord webhook details
const char* webhook_host = "discord.com";
const int webhook_port = 443;
const char* webhook_path = "/api/webhooks/############################################################";

// Message to send
const char* message = "Please revive the server!";

// WiFi client for HTTPS connection
WiFiClientSecure client;

// Light sleep duration: 1 hour (in microseconds)
const unsigned long sleepDuration = 3600e6;  // 1 hour = 3600 seconds = 3600e6 microseconds

void setup() {
  Serial.begin(115200);
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Default I2C address for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Display startup message
  showOLEDMessage("Starting...", 0, 0);

  // Connect to WiFi
  connectToWiFi();

  // Send the Discord message
  if (sendDiscordMessage(message)) {
    Serial.println("Message sent successfully!");
    showOLEDMessage("Message Sent!", 0, 16);
    delay(120000);
  } else {
    Serial.println("Failed to send message.");
    showOLEDMessage("Message Failed!", 0, 16);
    delay(120000);
  }

  // Display sleep info
  showOLEDMessage("Sleeping 1hr...", 0, 32);

  // Enter light sleep
  enterLightSleep(sleepDuration);
}

void loop() {
  // Empty - ESP8266 wakes up and restarts from setup()
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  showOLEDMessage("Connecting WiFi...", 0, 16);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
    delay(500);
    Serial.print(".");
    retryCount++;
    showOLEDMessage("Retrying WiFi...", 0, 16);
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    showOLEDMessage("WiFi Connected!", 0, 16);
  } else {
    Serial.println("\nFailed to connect to WiFi.");
    showOLEDMessage("WiFi Failed!", 0, 16);
  }
}

bool sendDiscordMessage(const char* msg) {
  client.setInsecure();  // Trust all certificates

  Serial.print("Connecting to Discord webhook...");
  if (!client.connect(webhook_host, webhook_port)) {
    Serial.println("Failed to connect to Discord.");
    return false;
  }
  Serial.println("Connected!");

  // Create JSON payload
  String payload = "{\"content\":\"" + String(msg) + "\"}";

  // Send HTTP POST request
  client.println("POST " + String(webhook_path) + " HTTP/1.1");
  client.println("Host: " + String(webhook_host));
  client.println("User-Agent: ESP8266");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(payload.length());
  client.println();  // End of headers
  client.println(payload);  // Send payload

  // Debug HTTP response
  Serial.println("Waiting for server response...");
  String response = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;  // End of headers
    response += line;  // Append headers to response for debugging
  }

  while (client.available()) {
    char c = client.read();
    response += c;
  }
  client.stop();

  // Print full response for debugging
  Serial.println("Full response from Discord:");
  Serial.println(response);

  // Check for 204 No Content
  if (response.indexOf("204 No Content") >= 0) {
    Serial.println("Message sent successfully!");
    return true;
  }
  Serial.println("Message failed to send. Response: " + response);
  return false;
}

void enterLightSleep(unsigned long duration) {
  WiFi.disconnect();  // Disconnect WiFi for sleep
  WiFi.mode(WIFI_OFF);
  delay(100);

  Serial.println("Entering light sleep...");
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_do_sleep(duration);

  delay(duration / 1000);  // Ensures the device sleeps
}

void showOLEDMessage(String message, int x, int y) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(x, y);
  display.println(message);
  display.display();
}