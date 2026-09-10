#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int x, minX;

// Update these with values suitable for your network.

const char* ssid = "#######";
const char* password = "##########";
const char* mqtt_server = "################";

WiFiClient espClient;
PubSubClient client(espClient);
// #define MSG_BUFFER_SIZE	100
// char msg[MSG_BUFFER_SIZE];
String msg = "Hello World!";

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void scrollMsg() {
  const int lcdWidth = 16;
  const int gap = 10;

  // Create 10-character padding
  String padding = "";
  for (int i = 0; i < gap; i++) {
    padding += " ";
  }

  // Append gap to message
  String scrollText = msg + padding;
  int totalSteps = scrollText.length();  // One full loop

  for (int i = 0; i < totalSteps; i++) {
    int start = i % scrollText.length();

    String display = "";
    if (start + lcdWidth <= scrollText.length()) {
      display = scrollText.substring(start, start + lcdWidth);
    } else {
      int firstPartLen = scrollText.length() - start;
      display = scrollText.substring(start) + scrollText.substring(0, lcdWidth - firstPartLen);
    }

    lcd.setCursor(0, 1);
    lcd.print(display);
    delay(250);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  // int value = String((char*) payload).toInt();
  // String(msg) = String((char*) payload);
  msg = String((char*)payload);
  Serial.println(msg);
  // Serial.println(topic);
  // Serial.println(msg);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("hass/adi_esp/output", "hello world");
      // ... and resubscribe
      client.subscribe("hass/adi_esp/input");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // msg = String("Hello World").c_str();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.noBacklight();
  lcd.clear();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  scrollMsg();
}