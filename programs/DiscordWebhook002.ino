#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi and MQTT Credentials (FILL THESE IN)
const char* ssid = "######";            // Replace with your Wi-Fi SSID
const char* password = "##########";    // Replace with your Wi-Fi password
const char* mqtt_server = "broker.hivemq.com";  // HiveMQ public broker
const char* mqtt_topic = "discord/alerts";      // MQTT topic to subscribe to

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Starting...");
  display.display();

  // Connect to Wi-Fi
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Connecting to WiFi...");
  display.display();
  Serial.println("[INFO] Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n[INFO] Wi-Fi connected.");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi Connected!");
  display.display();
  delay(1000);

  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Connecting to MQTT...");
  display.display();
  Serial.println("[INFO] Connecting to MQTT broker...");
  while (!client.connected()) {
    if (client.connect("WemosD1Mini")) {
      Serial.println("[INFO] MQTT connected.");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("MQTT Connected!");
      display.display();
      client.subscribe(mqtt_topic);
    } else {
      Serial.println("[ERROR] MQTT connection failed. Retrying...");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("MQTT Failed...");
      display.display();
      delay(5000);
    }
  }
}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  Serial.printf("[DEBUG] MQTT Message: %s\n", message);

  // Parse sender and timestamp
  String msg = String(message);
  int commaIndex = msg.indexOf(',');
  String sender = msg.substring(0, commaIndex);
  String timestamp = msg.substring(commaIndex + 1);

  // Display sender and timestamp on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("New Msg Received:");
  display.setCursor(0, 10);
  display.print("Sender: ");
  display.print(sender);
  display.setCursor(0, 20);
  display.print("Time: ");
  display.print(timestamp);
  display.display();
}