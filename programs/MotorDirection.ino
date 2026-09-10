#include <Arduino.h>

#define in1 5
#define in2 4

int rotDirection = 0;
int pressed = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.begin(115200);
  Serial.println("Helllo there");
}

void loop() {
  if (digitalRead(button) == HIGH){
    delay(100);
    if (digitalRead(button) == HIGH) {
      rotDirection = !rotDirection;
      Serial.println("Button pressed");
    }
  }
////  while(digitalRead(button) == true);
////  delay(20);
  if(rotDirection == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(200);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(200);    
  }

}
