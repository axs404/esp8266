int m1=14;
int m2=12;
int m3=13;
int m4=15;
int a;
void setup()
{
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  Serial.begin(9600);
  Serial.println("enter letter");
}
void loop()
{
  if (Serial.available())
  {
    a=Serial.read();
  } 
  switch(a)
  {
    case'f':
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    Serial.println("Going front...");
    break;
    case'b':
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    Serial.println("Going back...");
    break;
    case'r':
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    Serial.println("Turning right...");
    break;
    case'l':
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    Serial.println("Turning left...");
    break;
    case's':
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    Serial.println("Stopping...");
    break;
  }
}
