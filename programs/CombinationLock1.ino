int servoLed = 15;  
#define D1 1
#define D2 2
#define D3 3
#define D4 4
int LEDg = 11;
int LEDr = 12;
int buzzer = 13;
String password = "#####";
String enteredpassword = "";
String timesofpassword = "";
void beep();

void setup() {
  pinMode (servoLed, OUTPUT);
  pinMode (D1,INPUT);
  pinMode (D2,INPUT);
  pinMode (D3,INPUT);
  pinMode (D4,INPUT);
  
  pinMode (LEDg,OUTPUT);
  pinMode (LEDr,OUTPUT);
  pinMode (buzzer,OUTPUT);
  Serial.begin(9600);
   
}

void loop() {
  
  digitalWrite(D1, HIGH);
  delay(100);
  digitalWrite(D2, HIGH);
  delay(100);
  digitalWrite(D3, HIGH);
  delay(100);
  digitalWrite(D4, HIGH);
  delay(100);

   if (enteredpassword != "") {
    Serial.println(enteredpassword);
    delay(100);
   }
    
  if ( enteredpassword.length()==4)
  {

    if (enteredpassword == password)
    {
      beep();
      delay(200);
      beep();
      delay(200);    
      digitalWrite(LEDg, HIGH);
      delay(1000);
      digitalWrite(LEDg, LOW);
      digitalWrite(servoLed, HIGH);                  
    }
    else
    {
      
      beep();
      delay(200);
      beep();
      delay(200);
      beep();
      delay(200);
      digitalWrite(LEDr, HIGH);
      delay(1000);
      digitalWrite(LEDr,LOW);
      digitalWrite(servoLed, LOW);
    }
  enteredpassword="";
  }
   if (enteredpassword.length()==9)
   {
  
   }
   if (digitalRead(D1)==LOW)
   {
    enteredpassword+="1";
    beep();
   } 
   else if (digitalRead(D2)==LOW)
   {
     enteredpassword+="2";
     beep();
   }
   else if (digitalRead(D3)==LOW)
   {
      enteredpassword+="3";
      beep();
   }
   else if (digitalRead(D4)==LOW)
   {
      enteredpassword+="4";
      beep();
   }
}

void beep(){
  Serial.println("beep..");
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}
