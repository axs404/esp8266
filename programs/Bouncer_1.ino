#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
//#define D7 13
//#define D8 15

void setup() {
  // put your setup code here, to run once:
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
//  pinMode(D7, OUTPUT);
//  pinMode(D8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D1, HIGH);
  delay(150);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  delay(150);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  delay(150);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  delay(150);
  digitalWrite(D4, LOW);
  digitalWrite(D5, HIGH);
  delay(150);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  delay(150);  
  digitalWrite(D6, LOW);
  digitalWrite(D5, HIGH);
  delay(150);
  digitalWrite(D5, LOW);
  digitalWrite(D4, HIGH);
  delay(150);
  digitalWrite(D4, LOW);
  digitalWrite(D3, HIGH);
  delay(150);
  digitalWrite(D3, LOW);
  digitalWrite(D2, HIGH);
  delay(150);
  digitalWrite(D2, LOW);
}
