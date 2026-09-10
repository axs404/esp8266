#include <FastLED.h>

// === USER CONFIGURABLE VARIABLES ===
#define LED_PIN D5        // GPIO14 — data pin for LED strip
#define NUM_LEDS 12       // Number of LEDs in your strip
#define BRIGHTNESS 50     // Overall brightness (0-255)
#define LED_TYPE WS2812B  // Type of LED strip
#define COLOR_ORDER GRB   // Color order for your LED strip

#define BUTTON_PIN D6  // GPIO12 — button to change effects
// ===================================

CRGB leds[NUM_LEDS];

// === Button Logic Variables ===
bool buttonState = HIGH;
bool lastButtonReading = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long buttonPressedTime = 0;
unsigned long buttonReleasedTime = 0;
bool isLongPress = false;

const unsigned long debounceDelay = 50;
const unsigned long longPressThreshold = 1000;  // 1 second

// === Power State Tracking ===
bool isPoweredOn = true;

// Effect tracking
uint8_t currentEffect = 0;
const uint8_t numEffects = 20;

// Variables used across effects
uint8_t gHue = 0;
uint16_t pseudoTime = 0;
uint16_t lastMillis = 0;

// Noise variables for advanced effects
#define MAX_DIMENSION 16
uint16_t dist = 1234;
uint16_t x = 0, y = 0, z = 0;

void setup() {
  delay(1000);
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("RGB Controller with 20 Effects Ready.");
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Blue;
  FastLED.show();
  delay(300);
  FastLED.clear();
}

void loop() {
  handleButton();

  if (!isPoweredOn) return;  // Skip everything if power is off

  switch (currentEffect) {
    case 0: rainbow(); break;
    case 1: rainbowCycle(); break;
    case 2: meteorRain(); break;
    case 3: sinelon(); break;
    case 4: colorFadePulse(); break;
    case 5: rainbowGlitter(); break;
    case 6: colorWaves(); break;
    case 7: glitter(); break;
    case 8: fire(); break;
    case 9: cylon(); break;
    case 10: twinkle(); break;
    case 11: gradientFlow(); break;
    case 12: starfield(); break;
    case 13: rippleEffect(); break;
    case 14: noiseColorWash(); break;
    case 15: drip(); break;
    case 16: fire2012(); break;
    case 17: fireworksSparkle(); break;
    case 18: sparkleTrail(); break;
    case 19: snake(); break;
  }

  EVERY_N_MILLISECONDS(20) {
    FastLED.show();
  }
  gHue++;
}

// === Button Debounce ===
void handleButton() {
  bool currentReading = digitalRead(BUTTON_PIN);

  if (currentReading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentReading != buttonState) {
      buttonState = currentReading;

      // Button pressed
      if (buttonState == LOW) {
        buttonPressedTime = millis();
        isLongPress = false;
      }
      // Button released
      else {
        buttonReleasedTime = millis();
        unsigned long pressDuration = buttonReleasedTime - buttonPressedTime;

        if (pressDuration >= longPressThreshold) {
          isLongPress = true;
          handleLongPress();
        } else {
          handleShortPress();
        }
      }
    }
  }

  lastButtonReading = currentReading;
}

void handleShortPress() {
  if (!isPoweredOn) {
    powerOnStrip();
    return;
  }

  currentEffect = (currentEffect + 1) % numEffects;
  Serial.print("Short press: Switched to effect ");
  Serial.println(currentEffect);
}

void handleLongPress() {
  if (isPoweredOn) {
    powerDownStrip();
  }
}

void powerDownStrip() {
  FastLED.clear(true);  // Clear and show immediately
  isPoweredOn = false;
  Serial.println("Long press: Strip powered OFF.");
}

void powerOnStrip() {
  isPoweredOn = true;
  Serial.println("Power ON: Restoring effect.");
}

// === EFFECT FUNCTIONS ===
void rainbow() {
  fill_rainbow(leds, NUM_LEDS, millis() / 20, 7);
}

void rainbowCycle() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((i * 256 / NUM_LEDS + hue), 255, 255);
  }
  hue++;
}

void meteorRain() {
  CRGB color = CRGB::Red;            // Default color
  byte meteorSize = 10;              // Size of the meteor
  byte meteorTrailDecay = 64;        // How quickly the trail fades
  boolean meteorRandomDecay = true;  // Randomize trail decay
  int SpeedDelay = 1;                // Delay between frames

  for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      if ((!meteorRandomDecay) || (random(10) > 5)) {
        leds[j].fadeToBlackBy(meteorTrailDecay);
      }
    }
    for (int j = 0; j < meteorSize; j++) {
      if ((i - j < NUM_LEDS) && (i - j >= 0)) {
        leds[i - j] = color;
      }
    }
    FastLED.show();
    delay(SpeedDelay);
  }
}

void sinelon() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds[pos] += CHSV(millis() / 10, 255, 192);
}

void colorFadePulse() {
  static uint8_t hue = 0;
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, beatsin8(30, 128, 255)));
  hue++;
}

void rainbowGlitter() {
  fill_rainbow(leds, NUM_LEDS, millis() / 10, 7);
  if (random8() < 80) leds[random16(NUM_LEDS)] += CRGB::White;
}

void colorWaves() {
  uint8_t wave = beatsin8(9, 0, 255);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(wave + i * 8, 255, 255);
  }
}

void glitter() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  if (random8() < 80) {
    leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void fire() {
  static byte heat[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS) + 2));
  }
  for (int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  if (random8() < 128) {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }
  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = HeatColor(heat[j]);
  }
}

void cylon() {
  static int pos = 0;
  static int dir = 1;
  fadeToBlackBy(leds, NUM_LEDS, 20);
  leds[pos] = CRGB::Red;
  pos += dir;
  if (pos == NUM_LEDS - 1 || pos == 0) dir *= -1;
}

void twinkle() {
  fadeToBlackBy(leds, NUM_LEDS, 15);
  if (random8() < 40) leds[random16(NUM_LEDS)] += CHSV(gHue + random8(64), 200, 255);
}

void gradientFlow() {
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(gHue + i * 3, 255, 255);
}

void starfield() {
  fadeToBlackBy(leds, NUM_LEDS, 10);
  for (int i = 0; i < 3; i++) leds[random(NUM_LEDS)] = CRGB::White;
}

void rippleEffect() {
  static int center = 0;
  static int step = -1;
  static uint8_t color;
  if (step == -1) {
    center = random(NUM_LEDS);
    color = random8();
    step = 0;
  }
  fadeToBlackBy(leds, NUM_LEDS, 64);
  int pos = (center + step) % NUM_LEDS;
  leds[pos] = CHSV(color, 255, 255);
  pos = (center - step + NUM_LEDS) % NUM_LEDS;
  leds[pos] = CHSV(color, 255, 255);
  step++;
  if (step > NUM_LEDS) step = -1;
}

void noiseColorWash() {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t noise = inoise8(x + i * 5, millis() / 4);
    leds[i] = CHSV(noise, 200, 255);
  }
  x += 1;
  if (x > 65530) x = 0;
}

void drip() {
  fadeToBlackBy(leds, NUM_LEDS, 40);
  int pos = beatsin16(30, 0, NUM_LEDS - 1);
  leds[pos] = CHSV(gHue, 255, 255);
}

void fire2012() {
  static byte heat[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS) + 2));
  for (int k = NUM_LEDS - 1; k >= 2; k--) heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  if (random8() < 128) heat[random8(7)] = qadd8(heat[random8(7)], random8(160, 255));
  for (int j = 0; j < NUM_LEDS; j++) leds[j] = HeatColor(heat[j]);
}

void fireworksSparkle() {
  fadeToBlackBy(leds, NUM_LEDS, 40);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(random8(), 200, 255);
}

void sparkleTrail() {
  fadeToBlackBy(leds, NUM_LEDS, 30);
  int pos = beatsin16(20, 0, NUM_LEDS - 1);
  leds[pos] = CHSV(gHue, 200, 255);
}

void snake() {
  static uint8_t head = 0;
  fadeToBlackBy(leds, NUM_LEDS, 40);
  leds[head] = CHSV(gHue, 255, 255);
  head = (head + 1) % NUM_LEDS;
}