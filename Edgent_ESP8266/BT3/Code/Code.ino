#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLqoinRY12"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "aZitTz5pbTi8oGo0uO7LLc2cb0BgTP1G"

#define led 15 //D8 

char auth[] = "6NZYV7PiPRaVWWN1yWodI2a_VmFgLiMD";
char ssid[] = "MobiPhone";
char pass[] = "17042001";
#define PIN_UPTIME V6

BLYNK_WRITE(V5){
  int p = param.asInt();
  Serial.print(p);
  digitalWrite(led, p); 
}
BlynkTimer timer;

void myTimerEvent()
{
  Serial.print("OK");
  float celsius = 50;
//  int analogValue = analogRead(A0); //reading the sensor on A0
//  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
//  float celsius = millivolts/10;
//  Blynk.virtualWrite(V4, celsius); //sending to Blynk
}

void setup()
{
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);  // ket noi server 
   pinMode(led, OUTPUT);                                  
}
BLYNK_WRITE(V0)                     //  ham nay duoc goi den khi Widget Vo thay doi trang thai
{
   int pinValue = param.asInt();       // gan gia tri cua chan V0 cho bien pinValue
   
   if (pinValue == 1) {
   digitalWrite(led, HIGH);         // khi nhan nut gia tri pinValue bang 1, led sang
   }
   
   else {
   digitalWrite(led, LOW);        // khi nha nut gia tri pinValue bang 0, led tat
   }
}
void loop()
{
   Blynk.run();                   //chay chuong trinh Blynk
}
