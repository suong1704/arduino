/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLqoinRY12"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "aZitTz5pbTi8oGo0uO7LLc2cb0BgTP1G"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "aZitTz5pbTi8oGo0uO7LLc2cb0BgTP1G";


char ssid[] = "ss";
char pass[] = "123456789";

#define led D8;
int button ;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V0){
  button = param.asInt();
  if (button == 1){
    digitalWrite(led , HIGH);
    }
    else{
      digitalWrite(led , LOW);
      }
}
void loop()
{
  Blynk.run();
}
