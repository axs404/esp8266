#define trig 12
#define echo 13
#define D1 5
#define D2 4
#define D3 0

int duration = 0;
int distance = 0;

void setup()
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(D1 , OUTPUT);
  pinMode(D2 , OUTPUT);
  pinMode(D3 , OUTPUT);
 
  Serial.begin(9600);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);

}
void loop()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(500);
  digitalWrite(trig , LOW);

  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);

  if(distance >= 5 && distance <= 10)
    digitalWrite(D1, LOW);
  if(distance >= 15 && distance <= 20)
    digitalWrite(D2, LOW);
  if(distance >= 25 && distance <= 30)
    digitalWrite(D3, LOW);
  delay(500);
}     
