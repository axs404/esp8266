#include <FastLED.h>  //Download the library from: https://github.com/FastLED/FastLED
#define NUM_LEDS 12  //The number of LEDs goes here.
#define DATA_PIN 5  //Connect your addressable LED strip to this pin.

CRGB leds[NUM_LEDS];

void LinearReactive(int val, int brightness);
void BrightnessReactive(int val);
void CentreProgressive(int val, int brightness);
void EdgeProgressive(int val, int brightness);

void setup() { 
  Serial.begin(9600);
  
  pinMode(A0, INPUT); //Connect the "ENVELOPE" pin of sound detector to Analog pin 0.
  
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  
  
  for(int i=0; i<=NUM_LEDS; i++)  //Turn off all the LEDs.
  {
  leds[i] = CRGB::Black;
  }
  FastLED.show(); //Update the LED strip.
}

void loop() {
  int sensitivity = 512;  //Change the sensitivity from here. ranges from 0 to 1023.
  
  int data = analogRead(A0);
  
  Serial.println(data);
  
  if(data > sensitivity)
  { 
  data = sensitivity;
  }

  int val_1 = map(data, 0, sensitivity+1, 0, NUM_LEDS);
  int val_2 = map(data, 0, sensitivity+1, 0, 255);
  int val_3 = map(data, 0, sensitivity+1, 0, NUM_LEDS/2);

  LinearReactive(val_1, 100 /* Change brightness from here. ranges from 0 to 255 */);
  //BrightnessReactive(val_2);
  //CentreProgressive(val_3, 100 /* Change brightness from here. ranges from 0 to 255 */);
  //EdgeProgressive(val_3, 100 /* Change brightness from here. ranges from 0 to 255 */);
  
  FastLED.show(); //DO NOT MAKE THIS LINE A COMMENT.
}

void LinearReactive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[i] = CHSV(hue+=40,200,brightness);
  }

  for(int i=val+1; i<=NUM_LEDS; i++)
  {
  leds[i].nscale8(10);
  }
}

void BrightnessReactive(int val){
  int hue = 0;
  for(int i=0; i<=NUM_LEDS; i++)
  {
  leds[i] = CHSV(hue+=2,255,val);
  }
}

void CentreProgressive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[(NUM_LEDS/2)+i] = CHSV(hue+=20,255,brightness);
  leds[(NUM_LEDS/2)-i] = CHSV(hue+=20,255,brightness);
  }

  for(int i=val+1; i<=(NUM_LEDS/2); i++)
  {
  leds[(NUM_LEDS/2)+i].nscale8(10);
  leds[(NUM_LEDS/2)-i].nscale8(10);
  }
}

void EdgeProgressive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[i] = CHSV(hue+=20,255,brightness);
  leds[NUM_LEDS-i] = CHSV(hue+=20,255,brightness);
  }

  for(int i=val+1; i<=(NUM_LEDS/2); i++)
  {
  leds[i].nscale8(10);
  leds[NUM_LEDS-i].nscale8(10);
  }
}
