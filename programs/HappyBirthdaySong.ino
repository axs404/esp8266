#include <Arduino.h>

// these constants won't change:
const int ledCount = 6;    // the number of LEDs in the bar graph

int ledPins[] = {
  D0, D1, D2, D3, D4, D5
};   // an array of pin numbers to which LEDs are attached



int speakerPin = D6; // Buzzer pin
int length = 28; // the number of notes
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int tempo = 200;// time delay between notes 


void displayBarGraph(int tone) {
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(tone, 0, 1400, 0, ledCount);

  // loop over the LED array:
  for (int thisLed = ledCount-1; thisLed >=0; thisLed--) {
    digitalWrite(ledPins[thisLed], LOW);
    delayMicroseconds(500);
  } 

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledLevel; thisLed++) {
    digitalWrite(ledPins[thisLed], HIGH);
    delayMicroseconds(100);
  }    
}

void playTone(int tone, int duration) {
    displayBarGraph(2000-tone);
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
    displayBarGraph(0);
}

void playNote(char note, int duration) {
    char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                    'c', 'd', 'e', 'f', 'g', 'a', 'b',

                    'x', 'y' };

    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                    956,  834,  765,  593,  468,  346,  224,

                    655 , 715 };

    int SPEE = 5;

    // play the tone corresponding to the note name

    for (int i = 0; i < 17; i++) {
    if (names[i] == note) {
        int newduration = duration/SPEE;
        playTone(tones[i], newduration);
    }
    }
}


void setup() {
    Serial.begin(115200);
    pinMode(speakerPin, OUTPUT);
    // loop over the pin array and set them all to output:
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        pinMode(ledPins[thisLed], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
            delay(beats[i] * tempo); // delay between notes
        } else {
            playNote(notes[i], beats[i] * tempo);
        }
        
        // time delay between notes
        delay(tempo);
    }

}
