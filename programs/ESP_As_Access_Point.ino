#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led D4

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.softAP("ADI-ESP8266", "WeMos D1 Mini");
  Serial.println();
  Serial.println("ESP8266 started!");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(led, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
  }
}
