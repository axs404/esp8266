const int redPin = D5;
const int greenPin = D6;
const int bluePin = D7;
int redValue;
int greenValue;
int blueValue;
#define delayTime 250

void setup() {

  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, HIGH);
}

void loop() {

  int redValue = 255;
  int blueValue = 0;
  int greenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    greenValue += 1;
    redValue -= 1;
    analogWrite(greenPin, 255 - greenValue);
    analogWrite(redPin, 255 - redValue);

    delay(delayTime);
  }

  redValue = 0;
  blueValue = 0;
  greenValue = 255;
  for (int i = 0; i < 255; i += 1) {
    blueValue += 1;
    greenValue -= 1;
    analogWrite(bluePin, 255 - blueValue);
    analogWrite(greenPin, 255 - greenValue);

    delay(delayTime);
  }

  redValue = 0;
  blueValue = 255;
  greenValue = 0;
  for (int i = 0; i < 255; i += 1) {
    redValue += 1;
    blueValue -= 1;
    analogWrite(redPin, 255 - redValue);
    analogWrite(bluePin, 255 - blueValue);

    delay(delayTime);
  }
}