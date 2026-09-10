#include <Servo.h>

const int ServoPin = 2;
const int TrigPin = 12;
const int EchoPin = 13;

long  Duration, CM;

const int MinDistance = 5;
const int MaxDistance = 50;

int PrevPos = 90;

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(ServoPin);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  myservo.write(PrevPos);
  delay(2500);
}

void loop() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  pinMode(EchoPin, INPUT);
  Duration = pulseIn(EchoPin, HIGH);
  CM = (Duration / 2) * 0.0343;
  if (CM < MinDistance) {
    CM = MinDistance;
  }
  if (CM > MaxDistance) {
    CM = MaxDistance;
  }
  Serial.print("CM = ");
  Serial.println(CM);

  int NextPos = map(CM, 5, 50, 0, 180);
  while (NextPos > PrevPos) {
    PrevPos = PrevPos + 1;
    myservo.write(PrevPos);
    delay(20);
  }
  while (NextPos < PrevPos) {
    PrevPos = PrevPos - 1;
    myservo.write(PrevPos);
    delay(20);
  }
  delay(100);
}
