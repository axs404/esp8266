/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
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

// void callback(char* topic, byte* payload, unsigned int length) {
//   // Serial.print("Message arrived [");
//   // Serial.print(topic);
//   // Serial.print("] ");
//   for (int i = 12; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

void scrollMsg() {
  minX = -12 * strlen(msg.c_str());  // 12 = 6 pixels/character * text size 2

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(x,23);
  display.print(msg);
  display.display();
  x = x - 1; // scroll speed, make more positive to slow down the scroll
  if (x < minX) {
    x = display.width();
    // should check if new messages have arrived
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
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

void setup_wifi();
void scrollMsg();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup() {
  // msg = String("Hello World").c_str();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x = display.width();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  scrollMsg();
  // unsigned long now = millis();
  // if (now - lastMsg > 5000) {
  //   lastMsg = now;
  //   ++value;
  //   snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  //   Serial.print("Publish message: ");
  //   Serial.println(msg);
  //   client.publish("hass/adi_esp/output", msg);
  // }
}