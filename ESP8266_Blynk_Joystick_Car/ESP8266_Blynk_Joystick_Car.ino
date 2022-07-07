//ESP8266 Blynk Joystick Car
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLQM_ZzrBA"
#define BLYNK_DEVICE_NAME "Led"
#define BLYNK_AUTH_TOKEN "neSgVdVJuadehpjirBKllSXrW3uvIZZS"
char auth[] = "neSgVdVJuadehpjirBKllSXrW3uvIZZS";
char ssid[] = "ss";
char pass[] = "1234567891";

#define RightMotorSpeed       D5   //14 
#define RightMotorDir         D6   //12 




void openMotor(){
    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(RightMotorDir, HIGH);
  }


void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(RightMotorSpeed, OUTPUT);
//    pinMode(LeftMotorSpeed , OUTPUT);
    pinMode( RightMotorDir, OUTPUT);
//    pinMode(LeftMotorDir, OUTPUT);

//    digitalWrite(RightMotorSpeed, LOW);
//    digitalWrite(LeftMotorSpeed , LOW);
//    digitalWrite( RightMotorDir, HIGH);
//    digitalWrite(LeftMotorDir, HIGH);
}


void loop()
{
    Blynk.run();
}


BLYNK_WRITE(V0)
{
    int x = param.asInt();
    if (x == 1){
    
    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite( RightMotorDir, HIGH);
    Serial.print(x);
    }
    else{
      
      digitalWrite(RightMotorSpeed, LOW);
      digitalWrite( RightMotorDir, LOW);
      Serial.print(x);
      }
    
}
