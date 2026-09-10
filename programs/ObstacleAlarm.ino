#define D1 5
#define trigPin 12
#define echoPin 13

void setup() {
   Serial.begin(9600); 
   pinMode(D1, OUTPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
  

}

void loop() {
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);

  if(distance <= 50) {
    digitalWrite(D2, HIGH);
    delay(5);
  }

  else if(distance > 50) {
    digitalWrite(D2, LOW);
  }
      
}
