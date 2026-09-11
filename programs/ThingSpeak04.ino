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
int change;
int oldDistance = 0;  // Variable to store distance calculated using formula
int newDistance;
long duration;  // Variable to store time taken to the pulse to reach receiver
bool update;

void show(int a, int b, String c, bool update = true) {
  display.setCursor(a, b);
  display.println(c);
  if (update) {
    display.display();  // only refresh if requested
  }
}

void show(int a, int b, String c, bool update);
void connect();
void measure();
void thingspeaksend();

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
  show(0, 16, "Distance measurement", false);
  show(0, 32, "using ESP8266.", true);

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  connect();

  measure();

  change = newDistance - oldDistance;
  if(abs(change) > 5) {
    // it should send the changed distance to thingspeak
    thingspeaksend();
    Serial.println("Change of more than 5 cm detected in distance.");
    display.clearDisplay();
    show(0, 4,  "Change in", false);
    show(0, 20, "distance detected!", false);
    show(0, 36, "Distance:", false);
    show(60, 36, String(newDistance), true);  // last one updates
    if(update == true) {
      show(0, 52, "Update successful!", true);
    }
    else {
      show(0, 52, "Update failed!", true);
    }
    oldDistance = newDistance;
  }

  else {
    // it should not send any data to thingspeak
    Serial.println("Change of less than 5 cm detected in distance.");
    display.clearDisplay();
    show(0, 4,  "No change in", false);
    show(0, 20, "distance detected!", false);
    show(0, 36, "Distance:", false);
    show(60, 36, String(newDistance), true);  // last one updates
    oldDistance = newDistance;
  }
  
  delay(15000); // Wait 15 seconds to update the channel again
}

void connect() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    // Display Text
    display.clearDisplay();
    show(0, 8,  "Attempting to connect", false);
    show(0, 24, "to the SSID:", false);
    show(0, 40, SECRET_SSID, true);  // final update
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
    show(y, 54, "Connected!");
  }
}

void measure() {
  // function to check distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  // wait for 2 ms to avoid collision in serial monitor

  digitalWrite(trigPin, HIGH);  // turn on the Trigger to generate pulse
  delayMicroseconds(10);  // keep the trigger "ON" for 10 ms to generate pulse for 10 ms.

  digitalWrite(trigPin, LOW);  // Turn off the pulse trigger to stop pulse generation

  duration = pulseIn(echoPin, HIGH);
  newDistance = duration * 0.0344 / 2;  // Expression to calculate distance using time

  Serial.print("Distance: ");
  Serial.print(newDistance);  // Print the output in serial monitor
  Serial.println(" cm");
}

void thingspeaksend() {
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, newDistance, myWriteAPIKey);
  if(x == 200){
    update = true;
    Serial.println("Channel update successful.");
    // display.clearDisplay();
    // show(0, 4,  "Channel update", false);
    // show(0, 20, "successful!", false);
    // show(0, 36, "Distance:", false);
    // show(60, 36, String(newDistance), true);  // last one updates
  }
  else{
    update = false;
    Serial.println("Problem updating channel. HTTP error code " + String(x));
    // display.clearDisplay();
    // show(0, 8,  "Problem updating", false);
    // show(0, 24, "channel. HTTP", false);
    // show(0, 40, "error code:", false);
    // show(0, 56, String(x), true);  // last one triggers update
  }
}
