#include "Arduino.h"

void setup()
{
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, OUTPUT);    
  pinMode(D6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(D1) == HIGH) {
    Serial.print(1);
  
  }
  if(digitalRead(D2) == HIGH) {
    Serial.print(2);
  
  }
  if(digitalRead(D3) == HIGH) {
    Serial.print(3);
  
  }
  if(digitalRead(D4) == HIGH) {
    Serial.print(4);
  
  }
}
