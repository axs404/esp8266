#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

void zero();
void one();
void two();
void three();
void four();
void five();
void six();
void seven();
void eight();
void nine();

void setup () {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void zero () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D5, LOW);
  delay(500);
  digitalWrite(D7, LOW);
  delay(500);
  digitalWrite(D6, LOW);
  delay(500);
  digitalWrite(D3, LOW);
}

void one () {
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D6, LOW);
}

void two () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D5, LOW);
  delay(500);
  digitalWrite(D7, LOW);

}

void three () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D6, LOW);
  delay(500);
  digitalWrite(D7, LOW);

}

void four () {
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D6, LOW);
}

void five () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D6, LOW);
  delay(500);
  digitalWrite(D7, LOW);
}

void six () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D5, LOW);
  delay(500);
  digitalWrite(D7, LOW);
  delay(500);
  digitalWrite(D6, LOW);
  delay(500);
  digitalWrite(D4, LOW);
}

void seven () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D6, LOW);
}

void eight () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D6, LOW);
  delay(500);
  digitalWrite(D7, LOW);
  delay(500);
  digitalWrite(D5, LOW);
  delay(500);
  digitalWrite(D3, LOW);
}

void nine () {
  delay(500);
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
  digitalWrite(D6, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D6, LOW);
}

void loop() {
  zero();
  delay(500);
  one();
  delay(500);
  two();
  delay(500);
  three();
  delay(500);
  four();
  delay(500);
  five();
  delay(500);
  six();
  delay(500);
  seven();
  delay(500);
  eight();
  delay(500);
  nine();
  delay(500);
}
