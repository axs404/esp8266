#define trig 12
#define echo 13
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D8 15

int duration = 0;
int distance = 0;

void setup()
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
 
  pinMode(D1 , OUTPUT);
  pinMode(D2 , OUTPUT);
  pinMode(D3 , OUTPUT);
  pinMode(D4 , OUTPUT);
  pinMode(D5 , OUTPUT);
  pinMode(D8 , OUTPUT);
 
  Serial.begin(9600);

}

void loop()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
 

  if ( distance <= 5 )
  {
    digitalWrite(D1, HIGH);
  }
  else
  {
    digitalWrite(D1, LOW);
  }
  if ( distance <= 10)
  {
    digitalWrite(D2, HIGH);
  }
  else
  {
    digitalWrite(D2, LOW);
  }
  if ( distance <= 15)
  {
    digitalWrite(D3, HIGH);
  }
  else
  {
    digitalWrite(D3, LOW);
  }
  if ( distance <= 20)
  {
    digitalWrite(D4, HIGH);
  }
  else
  {
    digitalWrite(D4, LOW);
  }
  if ( distance <= 25)
  {
    digitalWrite(D5, HIGH);
  }
  else
  {
    digitalWrite(D5, LOW);
  }
  if ( distance <= 30)
  {
    digitalWrite(D8, HIGH);
  }
  else
  {
    digitalWrite(D8, LOW);
  }

}
