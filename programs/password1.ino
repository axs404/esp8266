int B1 = 5;
int B2 = 4;
int B3 = 0;
int B4 = 2;
String password = "####";
String enteredpassword = "";
String timesofpassword = "";
void setup() {
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
    digitalWrite(B1, LOW);
    delay(100);
    digitalWrite(B2, LOW);
    delay(100);
    digitalWrite(B3, LOW);
    delay(100);
    digitalWrite(B4, LOW);
    delay(100);
    if (enteredpassword != "") {
      Serial.println(enteredpassword);
      delay(100);
    }
    if (enteredpassword.length() == 4) {
      if (enteredpassword == password) {
        beep();
        delay(200);
        beep();
        delay(200);
        digitalWrite(LEDg, HIGH);
        delay(1000);
        digitalWrite(LEDg, LOW);      
        digitalWrite(servoLed, HIGH);
        delay(10000);
        digitalWrite(servoLed, LOW);
      }
    }
}
