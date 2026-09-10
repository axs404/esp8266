const int analogInPin = A0;
const int EN1 = 14;
const int OUT1  = 12;
const int OUT2  = 13;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(EN1, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = sensorValue;
  // change the analog out value:
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT2, LOW);
  analogWrite(EN1, outputValue);
  
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  Serial.print("output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
