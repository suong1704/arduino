
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLqoinRY12"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "aZitTz5pbTi8oGo0uO7LLc2cb0BgTP1G"



#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "aZitTz5pbTi8oGo0uO7LLc2cb0BgTP1G";
char ssid[] = "ss";
char pass[] = "@123456789/";
#define led 15 //D8 

BLYNK_WRITE(V0){
  int p = param.asInt();
  Serial.print(p);
  digitalWrite(led, p); 
}
void setup()
{

  Serial.begin(9600);
   pinMode(led, OUTPUT);    
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
