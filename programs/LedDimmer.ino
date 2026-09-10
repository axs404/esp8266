#define D1 5
#define D2 4
#define D3 0
void setup() {
  // put your setup code here, to run once:
   pinMode(D1, OUTPUT);
   pinMode(D2, OUTPUT);
   pinMode(D3, OUTPUT);
}
void loop() {
  while (true) {
  // put your main code here, to run repeatedly:
   int i=0;
   // increase brightness from 0 to max
   for (i=0; i<1250; i++) {
    analogWrite(D1, i);
    delay(5);
    analogWrite(D2, i);
    delay(5);
    analogWrite(D3, i);
    delay(5);
   }
    // decrease brightness from max to 0
   for (i=1250; i>0; i--) {
    analogWrite(D1, i);
    delay(5);
    analogWrite(D2, i);
    delay(5);
    analogWrite(D3, i);
    delay(5);   
    
    }
  } 
} 
