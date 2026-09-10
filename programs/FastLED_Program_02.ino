#include <FastLED.h>

// Number of RGB leds in the strand
#define NUM_LEDS 12
// Arduino pin used for data
#define LED_PIN 5

// Define the array of leds
CRGB leds[NUM_LEDS];

// The setup runs only once
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

// The loop routine runs over and over again forever
void loop() {
  // Read the input on analog pin A0
  int SensorValue1 = analogRead(A0);
  // Magnify the value
  int SensorValue2 = map(SensorValue1, 883, 1024, 1, 1024);
  // Reduce the value
  int LedNumber = map(SensorValue2, 1, 1024, 0, 11);
  // Make all the leds black
  for(int i = 0 ; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  // Light the leds depending on the value
  for(int j = 0 ; j < LedNumber ; j++) {
    leds[j] = CRGB::Blue;
    FastLED.show();
  }
  // Light the main led depending on the value
  leds[LedNumber] = CRGB::Red;
  FastLED.show();
  // Delay in between reads for stability
  delay(250);
}
