#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("########", "##########");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting.....");
    delay(200);
  }
  Serial.println("ESP8266 has connected!");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
