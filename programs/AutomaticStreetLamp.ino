int ldrPin = A0;
int led = 5;
int threshold = 100;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
void loop()
{
  int data = analogRead(ldrPin);
  Serial.println("");
  Serial.print("Brightness = ");
  Serial.print(data);
  if(data <= threshold)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  delay(10);
}
