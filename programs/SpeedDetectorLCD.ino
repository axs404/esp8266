#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaration of trigger and echo pins
int TrigPin = D5;
int EchoPin = D6;

// declaration of variables going to be used for the program
int distance1 = 0;
int distance2 = 0;
int measured_speed= 0;
long duration = 0;
int distance = 0;

void setup()
{
  // Setting trigger pin as OUTPUT
  pinMode(TrigPin, OUTPUT);

  // Setting EchoPin as INPUT
  pinMode(EchoPin, INPUT);

  // initialize the LCD
  lcd.begin();

  // Turn on the backlight
  // lcd.backlight();
  lcd.noBacklight();
}

void loop()
{
  // Measuring distance1
  distance1 = ultrasonicRead(); // calls ultrasoninicRead()
  delay(500);  // gives delay of 500 ms or half a second
  distance2 = ultrasonicRead(); // calls ultrasoninicRead() function below

  // Formula to calculate speed from distance1 and distance2
  // We are dividing it by 1, since the time interval between the two distance measurement is 500 ms or half a second
  measured_speed= abs(distance2 - distance1) / 0.5;

  // Clear the LCD for showing the new results
  lcd.clear();
  
  // Displaying the speed value on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Speed in cm/s: ");
  lcd.setCursor(0, 1);
  lcd.print(measured_speed);
}

// Function declaration to measure the distance based on the working principle of ultrasonic sensor
float ultrasonicRead()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(EchoPin, INPUT);
  duration = pulseIn(EchoPin, HIGH);
 
  // Convert the time into a distance
  distance = (duration/2) * 0.0343;     // Divide by 29.1 or multiply by 0.0343

  // returning measured distance
  return distance;
}