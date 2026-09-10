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

String readString;
int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600);
  delay(15);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {

  while (Serial.available()) {
    delay(250);  
    char c = Serial.read();
    Serial.print(c);
    // Display Text
    display.setCursor(x,y);
    display.print(c);
    display.display();
    readString += c;
    x = x + 11;
    if (x == 121) {
      x = 0;
      y = y + 16;
    }
  }
  // Clear the buffer.
  x = 0;
  y = 0;
  display.clearDisplay();
  delay(2000);
}