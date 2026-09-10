int leds[] = {5, 4, 0, 2, 14};
int N_LEDS = 5;

void setup() {
  for (int i=0; i<N_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  for (int i=0; i<N_LEDS; i++) {
    digitalWrite(leds[i], HIGH);
    delay(75);
  }
  for (int i=N_LEDS-1; i>=0; i--) {
    digitalWrite(leds[i], LOW);
    delay(75);
  }  
}
