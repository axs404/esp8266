/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98
This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

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

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int hSpin = 60;
int vSpin = 32;
int vSpin2 = 70;
int SpinRadius = 60;

void setup()   {     
  Serial.begin(115200);
  delay(15);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
}

void loop(){
  for(int i=60; i>0; i--){                       //Change loop to "for(int i=0; i<60; i++){" to spin clockwise
    display.fillRect(0, 0, 128, 64, BLACK);      //Blanks out last frame to black
    display.setTextColor(WHITE);
                              
    float SpinAngle = i * 6; 
    SpinAngle = SpinAngle / 57.296;
    float SpinAngle2 = SpinAngle + 90 / 57.296;
    
    int a = (hSpin + (sin(SpinAngle) * (SpinRadius / 2)));
    int b = (vSpin - (cos(SpinAngle) * (SpinRadius / 2)))/2;
    int c = (hSpin - (sin(SpinAngle) * (SpinRadius / 2)));
    int d = (vSpin + (cos(SpinAngle) * (SpinRadius / 2)))/2;

    int a1 = (hSpin + (sin(SpinAngle2) * (SpinRadius / 2)));
    int b1 = (vSpin - (cos(SpinAngle2) * (SpinRadius / 2)))/2;
    int c1 = (hSpin - (sin(SpinAngle2) * (SpinRadius / 2)));
    int d1 = (vSpin + (cos(SpinAngle2) * (SpinRadius / 2)))/2;

    int e = (hSpin + (sin(SpinAngle) * (SpinRadius / 2)));
    int f = (vSpin2 - (cos(SpinAngle) * (SpinRadius / 2)))/2;
    int g = (hSpin - (sin(SpinAngle) * (SpinRadius / 2)));
    int h = (vSpin2 + (cos(SpinAngle) * (SpinRadius / 2)))/2;

    int e1 = (hSpin + (sin(SpinAngle2) * (SpinRadius / 2)));
    int f1 = (vSpin2 - (cos(SpinAngle2) * (SpinRadius / 2)))/2;
    int g1 = (hSpin - (sin(SpinAngle2) * (SpinRadius / 2)));
    int h1 = (vSpin2 + (cos(SpinAngle2) * (SpinRadius / 2)))/2;
    
    display.drawLine(a,b,a1,b1,WHITE);
    display.drawLine(a1,b1,c,d,WHITE);
    display.drawLine(c,d,c1,d1,WHITE);
    display.drawLine(c1,d1,a,b,WHITE);

    display.drawLine(e,f+14,e1,f1+14,WHITE);
    display.drawLine(e1,f1+14,g,h+14,WHITE);
    display.drawLine(g,h+14,g1,h1+14,WHITE);
    display.drawLine(g1,h1+14,e,f+14,WHITE);
    
    display.drawLine(a,b,e,f+14,WHITE);
    display.drawLine(g,h+14,c,d,WHITE);
    display.drawLine(a1,b1,e1,f1+14,WHITE);
    display.drawLine(g1,h1+14,c1,d1,WHITE);

    display.display();                       // refresh screen
    delay(75);                               //Set delay to 1000 and mimick second hand movement
  }
}