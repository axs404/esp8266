int sensorPin = A0;   
int ledPin = 5;      
int sensorValue = 0;  

void setup() {
   pinMode(ledPin, OUTPUT);
}

void loop() {
   sensorValue = analogRead(sensorPin);
   
}
