#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Tilt sensor pin
const int tiltPin = D5;

// Variables for shake count and animation state
int shakeCount = 0;
bool isShaking = false;

void tiltAnimation();
void celebrationAnimation();

void setup() {
  pinMode(tiltPin, INPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Ready...");
  display.display();
}

void loop() {
  // Detect tilt sensor input
  if (digitalRead(tiltPin) == HIGH) {
    if (!isShaking) {
      isShaking = true;
      shakeCount++;
      tiltAnimation();
    }
  } else {
    isShaking = false;
  }

  // If shaken 10 times, display the final animation
  if (shakeCount >= 10) {
    celebrationAnimation();
    shakeCount = 0; // Reset shake count
  }
}

// Animation when the gift box tilts
void tiltAnimation() {
  display.clearDisplay();
  
  // Draw a tilting gift box
  display.fillRect(40, 30, 48, 30, SSD1306_WHITE); // Box
  display.fillRect(60, 15, 8, 15, SSD1306_WHITE);  // Ribbon vertical
  display.fillRect(40, 30, 48, 4, SSD1306_BLACK);  // Ribbon horizontal
  
  // Simulate tilt
  for (int i = 0; i < 5; i++) {
    display.clearDisplay();
    display.drawRect(40 + (i % 2 == 0 ? 3 : -3), 30, 48, 30, SSD1306_WHITE);
    display.display();
    delay(200);
  }
}

// Celebration animation
void celebrationAnimation() {
  display.clearDisplay();

  // Confetti and "Happy Marriage Anniversary"
  for (int i = 0; i < 20; i++) {
    int x = random(0, SCREEN_WIDTH);
    int y = random(0, SCREEN_HEIGHT - 16);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
  display.setTextSize(1);
  display.setCursor(10, SCREEN_HEIGHT - 10);
  display.println("Happy Marriage Anniversary!");

  // Draw balloons
  display.drawCircle(20, 20, 10, SSD1306_WHITE);
  display.drawCircle(100, 20, 10, SSD1306_WHITE);
  display.drawLine(20, 30, 20, 50, SSD1306_WHITE);
  display.drawLine(100, 30, 100, 50, SSD1306_WHITE);

  display.display();
  delay(3000); // Hold the display for 3 seconds
}