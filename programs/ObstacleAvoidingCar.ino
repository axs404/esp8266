#include <Servo.h>

Servo myservo;

const int in1 = D0;
const int in2 = D5;
const int in3 = D1;
const int in4 = D2;
const int servo = D6;
const int trigPin = D7;
const int echoPin = D8;
int angle = 90;
int bestAngle;
int distance;
int maxDistance;
long duration;
bool notFound = true;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  myservo.attach(servo, 500, 2500);
  pinMode(servo, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.write(angle);
  delay(100);
}

void loop() {
  servoSweep();
  Serial.print("Maximum Distance: ");
  Serial.println(maxDistance);
  Serial.print("Best Angle: ");
  Serial.println(bestAngle);
  myservo.write(bestAngle);
  checkDistance();
  movement();
  delay(100);
  angle = 0;
  bestAngle = 0;
  distance = 0;
  maxDistance = 0;
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void checkDistance() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.035) / 2;
}

void servoSweep() {
  for (angle = 90; angle >= 0; angle -= 5) {
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(", Distance: ");
    Serial.println(distance);
    myservo.write(angle);
    checkDistance();
    if (distance > maxDistance) {
      maxDistance = distance;
      bestAngle = angle;
    }
    delay(100);
  }
  for (angle = 0; angle <= 180; angle += 5) {
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(", Distance: ");
    Serial.println(distance);
    myservo.write(angle);
    checkDistance();
    if (distance > maxDistance) {
      maxDistance = distance;
      bestAngle = angle;
    }
    delay(100);
  }
  for (angle = 180; angle >= 90; angle -= 5) {
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(", Distance: ");
    Serial.println(distance);
    myservo.write(angle);
    checkDistance();
    if (distance > maxDistance) {
      maxDistance = distance;
      bestAngle = angle;
    }
    delay(100);
  }
}

void forwardmovement() {
  if (distance >= (maxDistance - 5) && distance <= (maxDistance + 5)) {
    Serial.println("[INFO] Distance within range, moving forward");
    while (distance > 10) {
      Serial.print("[DEBUG] Moving Forward, Current Distance: ");
      Serial.println(distance);
      forward();
      checkDistance();
      delay(100);
    }
    if (distance <= 10) {
      stop();
    }
  }
}

void movement() {
  Serial.println("[INFO] Starting movement function");

  while (bestAngle < 90) {
    Serial.print("[DEBUG] Best Angle: ");
    Serial.print(bestAngle);
    Serial.println("[INFO] bestAngle < 90, entering adjustment loop");
    Serial.println("[INFO] Starting to move left");
    left();
    delay(100);
    stop();
    Serial.println("[INFO] Stopped moving left");
    delay(100);
    notFound = true;
    for (angle = bestAngle; angle <= 90; angle += 5) {
      Serial.print("[DEBUG] For loop for servo movement started, the current notFound state is: ");
      Serial.println(notFound);
      Serial.print("[DEBUG] Searching for the bestAngle, the current angle is: ");
      Serial.println(angle);
      delay(100);
      if (notFound == true) {
        Serial.print("[DEBUG] notFound is true, the current angle is: ");
        Serial.println(angle);
        delay(100);
        myservo.write(angle);
        checkDistance();
        if (distance >= (maxDistance - 5) && distance <= (maxDistance + 5)) {
          Serial.print("[DEBUG] maxDistance found at: ");
          Serial.println(angle);
          delay(100);
          bestAngle = angle;
          notFound = false;
        }
      }
    }
  }

  while (bestAngle > 90) {
    Serial.print("[DEBUG] Best Angle: ");
    Serial.print(bestAngle);
    Serial.println("[INFO] bestAngle > 90, entering adjustment loop");
    Serial.println("[INFO] Starting to move right");
    right();
    delay(100);
    stop();
    Serial.println("[INFO] Stopped moving right");
    delay(100);
    notFound = true;
    for (angle = bestAngle; angle >= 90; angle -= 5) {
      Serial.print("[DEBUG] For loop for servo movement started, the current notFound state is: ");
      Serial.println(notFound);
      Serial.print("[DEBUG] Searching for the bestAngle, the current angle is: ");
      Serial.println(angle);
      delay(100);
      if (notFound == true) {
        Serial.print("[DEBUG] notFound is true, the current angle is: ");
        Serial.println(angle);
        delay(100);
        myservo.write(angle);
        checkDistance();
        if (distance >= (maxDistance - 5) && distance <= (maxDistance + 5)) {
          Serial.print("[DEBUG] maxDistance found at: ");
          Serial.println(angle);
          delay(100);
          bestAngle = angle;
          notFound = false;
        }
      }
    }
  }

  if (bestAngle == 90) {
    Serial.println("[INFO] The bestAngle is 90 degrees now");
    forwardmovement();
  }
  Serial.println("[INFO] Movement function completed");
}