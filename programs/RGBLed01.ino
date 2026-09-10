#define D1 5
#define D2 4
#define D3 0

void setup() {
  // put your setup code here, to run once:
  pinMode(D1 , OUTPUT);
  pinMode(D2 , OUTPUT);
  pinMode(D3 , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D1, LOW);
  delay(1250);
  digitalWrite(D1, HIGH);
  delay(1250);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  delay(1250);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  delay(1250);
  digitalWrite(D2, LOW);
  delay(1250);
  digitalWrite(D2, HIGH);
  delay(1250);
  digitalWrite(D3, LOW);
  delay(1250);
  digitalWrite(D3, HIGH);
  delay(1250);
}
