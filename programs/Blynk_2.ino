#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RightMotorSpeed       14   //D5 
#define RightMotorDir         12   //D6 
#define LeftMotorSpeed        13   //D7 
#define LeftMotorDir          15   //D8 

char auth[] = "####";
char ssid[] = "#######";
char pass[] = "########";

int minRange = 312;
int maxRange = 712;

int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;


void moveControl(int x, int y)
{
//Move Forward
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed, maxspeed);
        analogWrite(LeftMotorSpeed , maxspeed);
    }


//Move Forward Right
    else if(x >= maxRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir, HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Forward Left
    else if(x <= minRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }

//No Move
    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        analogWrite(RightMotorSpeed,nospeed);
        analogWrite(LeftMotorSpeed , nospeed);
    }

//Move Backward
    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Right
    else if(y <= minRange && x <= minRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Left
    else if(y <= minRange && x >= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }
}

void moveControl(int x, int y);

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(RightMotorSpeed, OUTPUT);
    pinMode(LeftMotorSpeed , OUTPUT);
    pinMode( RightMotorDir, OUTPUT);
    pinMode(LeftMotorDir, OUTPUT);

    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(LeftMotorSpeed , LOW);
    digitalWrite( RightMotorDir, HIGH);
    digitalWrite(LeftMotorDir, HIGH);
}


void loop()
{
    Blynk.run();
}


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}
