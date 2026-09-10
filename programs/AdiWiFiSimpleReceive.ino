/*
  ArduinoMqttClient - WiFi Simple Receive

  This example connects to a MQTT broker and subscribes to a single topic.
  When a message is received it prints the message to the serial monitor.

  The circuit:
  - Arduino MKR 1000, MKR 1010 or Uno WiFi Rev.2 board

  This example code is in the public domain.
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <ArduinoMqttClient.h>
//#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
//  #include <WiFiNINA.h>
//#elif defined(ARDUINO_SAMD_MKR1000)
//#include <WiFi101.h>
//#elif defined(ARDUINO_ESP8266_ESP12)
  #include <ESP8266WiFi.h>
//#endif

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "########";        // your network SSID (name)
char pass[] = "##########";    // your network password (use for WPA, or use as key for WEP)

// To connect with SSL/TLS:
// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate
//    flashed in the WiFi module.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//const char broker[] = "test.mosquitto.org";
//const char topic[]  = "arduino/adi";

const char broker[] = "#############";
const char topic[]  = "hass/wlid/d01";

int        port     = 1883;

void setup() {
  //Initialising the lcd
  lcd.init();
  //Switch on the backlight
  lcd.backlight();
  //Clearing the display
  lcd.clear();
  //Printing that the wemos has started
  lcd.setCursor(0,0);
  lcd.print("Starting...");
  delay(2000);

  //Initialize serial and wait for port to open:
  //Serial.begin(9600);

  //attempting to connect to Wifi network:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  //Serial.print("Attempting to connect to WPA SSID: ");
  //Serial.println(ssid);
  int i = 8;
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    lcd.setCursor(i,1);
    lcd.print(".");
    delay(5000);
    i++;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You're connected");
  lcd.setCursor(0,1);
  lcd.print("to");
  lcd.setCursor(3,1);
  lcd.print(ssid);
  //Serial.println("You're connected to the network");
  //Serial.println();
  delay(2000);
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Borewell = ");

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  //Serial.print("Attempting to connect to the MQTT broker: ");
  //Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    //Serial.print("MQTT connection failed! Error code = ");
    //Serial.println(mqttClient.connectError());

    while (1);
  }

  //Serial.println("You're connected to the MQTT broker!");
  //Serial.println();

  //Serial.print("Subscribing to topic: ");
  //Serial.println(topic);
  //Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  //Serial.print("Waiting for messages on topic: ");
  //Serial.println(topic);
  //Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    //Serial.print("Received a message with topic '");
    //Serial.print(mqttClient.messageTopic());
    //Serial.print("', length ");
    //Serial.print(messageSize);
    //Serial.println(" bytes:");

    int i = 0;

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      //This msg can also be printed to an LCD
      //Serial.print((char)mqttClient.read());
      char c = (char)mqttClient.read();
      if (i==12 || i==13 || i==14) {
        if (c != '"') {
          //Serial.print(c);
          lcd.setCursor(i,1);
          lcd.print(c); 
        }
      }
      i++;
    }
    //Serial.println();

    //Serial.println();
  }
}
