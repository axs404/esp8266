#define redPin 8
#define greenPin 9
#define bluePin 10
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 1024 - red;
    green = 1024 - green;
    blue = 1024 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void loop()
{
  setColor(1024,0,0);  
  delay(1000);
  setColor(1024,1024,0);
  delay(1000);
  setColor(0,1024,0);
  delay(1000);
  setColor(0,1024,1024);  
  delay(1000);  
  setColor(0,0,1024);  
  delay(1000);
  setColor(1024,0,1024);
  delay(1000);
  setColor(1024,1024,1024);
  delay(1000);  
}
