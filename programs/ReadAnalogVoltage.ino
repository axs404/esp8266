void setup() {
  Serial.begin(9600);
}
void loop() {
  delay(1000);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
}
