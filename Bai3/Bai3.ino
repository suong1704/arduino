
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLJlojbEIs"
#define BLYNK_DEVICE_NAME "BT3"
#define BLYNK_AUTH_TOKEN "Tw5dSvmd1h887vLKHXG85iN-P2DE1OZO"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <SimpleTimer.h>


char auth[] = "Tw5dSvmd1h887vLKHXG85iN-P2DE1OZO";
char ssid[] = "ss";
char pass[] = "1234567891";

//SimpleTimer timer;


void readSensor(){

//  int analogValue = analogRead(A0); //
//  float millivolts = (analogValue/1024.0) * 3300; //3300 điện áp được cung cấp bởi NodeMCU 
//  float celsius = millivolts/10; 
  
  int sensor = analogRead(A0);
  float voltage = (float)(sensor * (3.3 / 1024));
  float tempC = voltage*100.0;
  Serial.print("Nhiet do: " + (String)tempC);
  Blynk.virtualWrite(V2, tempC);
  delay(1000);
  }
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
//  Blynk.begin(auth, ssid, pass);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
//  Blynk.begin(auth, ssid, pass, IPAddress(192,168,43,246), 80);
//  timer.setInterval(1000L, readSensor);
}

BLYNK_WRITE(V1)
{
    int x = param.asInt();
    if (x == 1){
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    Serial.print("Bat: "+(String)x);
    }
    else{
      
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      Serial.print("Bat: "+(String)x);
      }
    
}
float t;
void loop()
{
  
  Blynk.run();
//  timer.run();
  readSensor();
//  t = readSensor();
//  Serial.print("Nhiet do: " + (String)t);
//  t = random(0,100);
  
}
