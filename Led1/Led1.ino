
#define BLYNK_PRINT Serial

 #define BLYNK_TEMPLATE_ID "TMPLQM_ZzrBA"
#define BLYNK_DEVICE_NAME "Led"
#define BLYNK_AUTH_TOKEN "neSgVdVJuadehpjirBKllSXrW3uvIZZS"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "neSgVdVJuadehpjirBKllSXrW3uvIZZS";


char ssid[] = "ss";
char pass[] = "1234567891";

int button ;
void setup()
{
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V0){
  button = param.asInt();
  if (button == 1){
    Serial.print(button);
    analogWrite(A0 , HIGH);
    }
    else{
      Serial.print(button);
      analogWrite(A0 , LOW);
      }
}
void loop()
{
  Blynk.run();
}
