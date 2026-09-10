//MAX7219 - using Led Control library to display 8x8 bitmap
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <LedControl.h>

// Replace with your network credentials
const char* ssid = "########";
const char* password = "##########";

int DIN = 5;
int CS = 4;
int CLK = 0;
LedControl lc=LedControl(DIN, CLK, CS,0);

byte spriteAR1[] = { B00000000,B00010000,B00001000,B11111100,B00001000,B00010000,B00000000,B00000000};
byte spriteAR2[8] = { B00000000,B00001000,B00000100,B01111110,B00000100,B00001000,B00000000,B00000000};
byte spriteAR3[8] = { B00000000,B00000100,B00000010,B00111111,B00000010,B00000100,B00000000,B00000000};
byte spriteAR4[8] = { B00000000,B00000010,B00000001,B10011111,B00000001,B00000010,B00000000,B00000000};
byte spriteAR5[8] = { B00000000,B00000001,B10000000,B01000111,B10000000,B00000001,B00000000,B00000000};
byte spriteAR6[8] = { B00000000,B10000000,B01000000,B11100011,B01000000,B10000000,B00000000,B00000000};
byte spriteAR7[8] = { B00000000,B10000000,B01000000,B11100011,B01000000,B10000000,B00000000,B00000000};

void setup() {
  /* OTA Start */
 
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /* OTA END */
   
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
}

void displayChar(byte logo[], int delayTime) {
  for(int i=0;i<8;i++) lc.setRow(0,i,logo[i]);
  delay(delayTime);
  lc.clearDisplay(0);  
}
 
void loop(){
  ArduinoOTA.handle();
 
   
 displayChar(spriteAR1, 200);  
 displayChar(spriteAR2, 200);  
 displayChar(spriteAR3, 200);  
 displayChar(spriteAR4, 200);  
 displayChar(spriteAR5, 200);  
 displayChar(spriteAR6, 200);  
 displayChar(spriteAR7, 200);  
}
