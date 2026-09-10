/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL31rKJJ6bu"
#define BLYNK_TEMPLATE_NAME "Blynk Car"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <Servo.h>
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// // The pins for I2C are defined by the Wire-library. 
// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// create servo object to control a servo
Servo myservo;
// twelve servo objects can be created on most boards

int servo = D1;
int sc = D2;
int in1 = D5;
int in2 = D6;
int in3 = D7;
int in4 = D8;
int speed = 900;
int height = 0;
int forward;
int backward;
int left;
int right;

void setup()
{
  Serial.begin(115200);
  delay(100);

  // // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
  // }

  // // Set some initial values for the OLED display
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // // Clear the buffer
  // display.clearDisplay();

  myservo.attach(servo, 500, 2500);     // attach the servo on D3 to the servo object
  pinMode(sc, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(servo, OUTPUT);

  analogWrite(sc, speed);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V0) {
  height = param.asInt();
  Serial.print("Height: ");
  Serial.println(height);
  // pheight();
  myservo.write(height);  // tell servo to go to position in variable 'height'
  delay(15);           // waits 15ms for the servo to reach the position
}

BLYNK_WRITE(V1) {
  forward = param.asInt();
  Serial.print("Forward: ");
  Serial.println(forward);
  // pforward();
  if (forward == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (forward == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V2) {
  backward = param.asInt();
  Serial.print("Backward: ");
  Serial.println(backward);
  // pbackward();
  if (backward == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (backward == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

BLYNK_WRITE(V3) {
  right = param.asInt();
  Serial.print("Clockwise: ");
  Serial.println(right);
  // pclockwise();
  if (right == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  if (right == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

BLYNK_WRITE(V4) {
  left = param.asInt();
  Serial.print("Counterclockwise: ");
  Serial.println(left);
  // pcounterclockwise();
  if (left == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  if (left == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V5) {
  speed = param.asInt();
  Serial.print("Speed: ");
  Serial.println(speed);
  // pspeed();
  analogWrite(sc, speed);
  delay(15);
}

// void pheight() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,10);
//   display.print("Height: ");
//   display.setCursor(0,38);
//   display.print(height);
//   display.display();
//   Serial.println("Height done!");
// }

// void pforward() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,10);
//   display.print("Forward: ");
//   display.setCursor(0,38);
//   display.print(forward);
//   display.display();
//   Serial.println("Forward done!");
// }

// void pbackward() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,10);
//   display.print("Backward: ");
//   display.setCursor(0,38);
//   display.print(backward);
//   display.display();
//   Serial.println("Backward done!");
// }

// void pclockwise() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,10);
//   display.print("Clockwise: ");
//   display.setCursor(0,38);
//   display.print(right);
//   display.display();
//   Serial.println("Clockwise done!");
// }

// void pcounterclockwise() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,1);
//   display.print("Counter-");
//   display.setCursor(0,22);
//   display.print("Clockwise:");
//   display.setCursor(0,43);
//   display.print(left);
//   display.display();
//   Serial.println("Counterclockwise done!");
// }

// void pspeed() {
//   // Display Text
//   display.clearDisplay();
//   display.setCursor(0,10);
//   display.print("Speed:");
//   display.setCursor(0,38);
//   display.print(speed);
//   display.display();
//   Serial.println("Speed done!");
// }