#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPLqoinRY12"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "6NZYV7PiPRaVWWN1yWodI2a_VmFgLiMD"

char auth[] = "6NZYV7PiPRaVWWN1yWodI2a_VmFgLiMD";
char ssid[] = "ss";
char pass[] = "@123456789/";
#define PIN_UPTIME V6
BLYNK_READ(PIN_UPTIME)
{
  Blynk.virtualWrite(PIN_UPTIME, millis() / 1000);
}

BlynkTimer timer;

void myTimerEvent()
{
  int analogValue = analogRead(A0); //reading the sensor on A0
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;
  Blynk.virtualWrite(V5, celsius); //sending to Blynk
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
