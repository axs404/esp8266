#define enA 5
#define in1 4
#define in2 0

int rotDirection = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void loop() {
  int potValue = analogRead(A0);
  int pwmOutput = map(potValue, 0, 1023, 0, 255);
  analogWrite(enA, pwmOutput);
}
