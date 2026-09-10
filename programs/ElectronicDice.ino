int topLeft = 5;
int topRight = 4;
int middleLeft = 0;
int middle = 2;
int middleRight = 14;
int bottomLeft = 12;
int bottomRight = 13;

int trigger = 0;

long r;

int inputPin = 15;

void setup() {
  randomSeed(analogRead(0));  

  pinMode(topLeft, OUTPUT);
  pinMode(topRight, OUTPUT);
  pinMode(middleLeft, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(middleRight, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  
  pinMode(inputPin, INPUT);
}

void loop() {
  if (digitalRead(inputPin) == HIGH && trigger == 0) {  
    trigger = 1;                                        
    r = random(1, 7);                                   

    int rolling;                                        
    for (rolling = 0; rolling < 100; rolling++) {       
    randomRoll(50);                    
    }


    if (r == 1) {
      one();
    }
    if (r == 2) {
      two();
    }
    if (r == 3) {
      three();
    }
    if (r == 4) {
      four();
    }
    if (r == 5) {
      five();
    }
    if (r == 6) {
      six();
    }
    delay(5000);
    clearPins();
    trigger = 0;
  }
}

void clearPins() {
  digitalWrite(topLeft, LOW);
  digitalWrite(topRight, LOW);
  digitalWrite(middleLeft, LOW);
  digitalWrite(middle, LOW);
  digitalWrite(middleRight, LOW);
  digitalWrite(bottomLeft, LOW);
  digitalWrite(bottomRight, LOW);
}

void one() {
  digitalWrite(middle, HIGH);
}

void two() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void three() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void four() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void five() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void six() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(middleLeft, HIGH);
  digitalWrite(middleRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void randomRoll(int roll) {
  int r;
  r = random(1, 8);
  digitalWrite(r, HIGH);
  if (roll > 0) {       
    delay(roll);
  }
  else if (roll == 0) {
    do {}
    while (1);
  }
  digitalWrite(r, LOW);
}