#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "#############";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "############";
char pass[] = "################";

#define EN1 14
#define OUT1 12
#define OUT2 13


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT2, LOW);
  analogWrite(EN1, pinValue);
  delay(100);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
