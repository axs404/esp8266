int trigPin = 12;
int echoPin = 13;
int in1 = 5;      
int in2 = 4;      
int in3 = 0;       
int in4 = 2;       
int c = 0;

void setup() {
   Serial.begin(9600); 
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);
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
 
  
  if((distance>20))
 {
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
 }
 
  else if(distance<20)  
 {
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   digitalWrite(in3, HIGH);                                  
   digitalWrite(in4, LOW);
                                            
 }
 
}