
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLEgBsa-oC"
#define BLYNK_DEVICE_NAME "BT3"
#define BLYNK_AUTH_TOKEN "R1kuYpwDJHtQBqkYazYqIAxjLNgL-5wp"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "R1kuYpwDJHtQBqkYazYqIAxjLNgL-5wp";
char ssid[] = "ss";
char pass[] = "1234567891";




void readSensor(){ 
  String tempC = "";
  while(Serial.available()) {
      char c = Serial.read();
      tempC = tempC + c ;
  }
  float temperature ;
  temperature = tempC.toFloat();
  
//  Serial.println("Nhiet do: " + (String)temperature);
  Blynk.virtualWrite(V2, temperature);
  delay(1000);
  }
void setup()
{
  Serial.begin(9600);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
//  Blynk.begin(auth, ssid, pass);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

BLYNK_WRITE(V1)
{
    int x = param.asInt();
    if (x == 1){
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    }
    else{
      
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      }
}

void loop()
{
  Blynk.run();
  readSensor();
  
}
