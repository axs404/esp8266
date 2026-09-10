#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "####";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "#######";
char pass[] = "########";

int Speed = 950;
int en1 = 5;
int m1 = 14;
int m2 = 12;
int en2 = 4;
int m3 = 13;
int m4 = 15;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(en1, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
 
}
 
// This function will be called every time button Widget
// in Blynk app writes values to the Virtual Pin V3

BLYNK_WRITE(V1) {
  int f = param.asInt();
  if (f == 0) {
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
     analogWrite(en1, 0);
     analogWrite(en2, 0);
  } 
  if (f == 1) {
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(en1, Speed);
    analogWrite(en2, Speed);
  }
}
BLYNK_WRITE(V2) {
  int b = param.asInt();
  if (b == 0) {
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
     analogWrite(en1, 0);
     analogWrite(en2, 0);
  } 
  if (b == 1) {
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(en1, Speed);
    analogWrite(en2, Speed);
  }
}
BLYNK_WRITE(V3) {
  int a = param.asInt();
  if (a == 0) {
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
     analogWrite(en1, 0);
     analogWrite(en2, 0);
  } 
  if (a == 1) {
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(en1, Speed);
    analogWrite(en2, Speed);
  }
}
BLYNK_WRITE(V4) {
  int c = param.asInt();
  if (c == 0) {
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
     analogWrite(en1, 0);
     analogWrite(en2, 0);
  } 
  if (c == 1) {
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(en1, Speed);
    analogWrite(en2, Speed);
  }
}
