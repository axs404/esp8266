#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

}

void loop() {
  digitalWrite(D1, HIGH);
  delay(100);
  digitalWrite(D1, LOW);
  delay(100);
  digitalWrite(D2, HIGH);
  delay(100);
  digitalWrite(D2, LOW);
  delay(100);
  digitalWrite(D3, HIGH);
  delay(100);
  digitalWrite(D3, LOW);
  delay(100);
  digitalWrite(D4, HIGH);
  delay(100);
  digitalWrite(D4, LOW);
  delay(100);
  digitalWrite(D5, HIGH);
  delay(100);
  digitalWrite(D5, LOW);
  delay(100);
  digitalWrite(D6, HIGH);
  delay(100);
  digitalWrite(D6, LOW);
  delay(100);
  digitalWrite(D7, HIGH);
  delay(100);
  digitalWrite(D7, LOW);
  delay(100);
  digitalWrite(D8, HIGH);
  delay(100);
  digitalWrite(D8, LOW);
  delay(100);
}
