const int ENA = 5;
const int OUT1  = 4;
const int OUT2  = 0;

void setup()

{
  
    pinMode(ENA, OUTPUT);
    pinMode(OUT1, OUTPUT);
    pinMode(OUT2, OUTPUT);
    digitalWrite(OUT1, HIGH);
    digitalWrite(OUT2, LOW);
    
}

void loop()    
  for (int i=0; i<1023; i+=10) {
    analogWrite(ENA, i);
    delay(10);
  }
  for (int i=1023; i>0; i-=10) {
    analogWrite(ENA, i);
    delay(10);
  }
} 
