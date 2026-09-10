#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

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

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

#define trigPin 14       // attach pin D10 Arduino to pin Trig of HC-SR04
#define echoPin 12       // attach pin D9 Arduino to pin Echo of HC-SR04

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int y = 0;
long duration;  // Variable to store time taken to the pulse to reach receiver
int distance;  // Variable to store distance calculated using formula

void setup() {
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  pinMode(trigPin, OUTPUT);     // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);      // Sets the echoPin as an INPUT

  Serial.println("Distance measurement using ESP8266.");
  // Display Text
  display.setCursor(0,16);
  display.println("Distance measurement");
  display.setCursor(0,32);
  display.println("using ESP8266.");
  display.display();

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    // Display Text
    display.clearDisplay();
    display.setCursor(0,8);
    display.println("Attempting to connect");
    display.setCursor(0,24);
    display.println("to the SSID:");
    display.setCursor(0,40);
    display.println(SECRET_SSID);
    display.display();
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      // Display Text
      display.setCursor(y,54);
      display.println(".");
      display.display();
      y = y + 1;
      delay(5000);
    } 
    Serial.println("\nConnected.");
    display.setCursor(y,54);
    display.println("Connected!");
    display.display();
  }

  // function to check distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  // wait for 2 ms to avoid collision in serial monitor

  digitalWrite(trigPin, HIGH);  // turn on the Trigger to generate pulse
  delayMicroseconds(10);  // keep the trigger "ON" for 10 ms to generate pulse for 10 ms.

  digitalWrite(trigPin, LOW);  // Turn off the pulse trigger to stop pulse generation

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;  // Expression to calculate distance using time

  Serial.print("Distance: ");
  Serial.print(distance);  // Print the output in serial monitor
  Serial.println(" cm");

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, distance, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
    display.clearDisplay();
    display.setCursor(0,8);
    display.println("Channel update");
    display.setCursor(0,24);
    display.println("successful!");
    display.setCursor(0,40);
    display.println("Distance (cm):");
    display.setCursor(0,56);
    display.println(distance);
    display.display();
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
    display.clearDisplay();
    display.setCursor(0,8);
    display.println("Problem updating");
    display.setCursor(0,24);
    display.println("channel. HTTP");
    display.setCursor(0,40);
    display.println("error code: ");
    display.setCursor(0,56);
    display.println(String(x));
    display.display();
  }
  
  delay(60000); // Wait 15 seconds to update the channel again
}
