#include <SoftwareSerial.h>

const byte RX = 2; //receive
const byte TX = 3; // send
SoftwareSerial mySerial = SoftwareSerial(RX,TX);

void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600);
  pinMode(4, OUTPUT);
//  pinMode(5, OUTTPUT);

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  Serial.println("ABC");
  Send();
 delay(100);
}
void Send(){
//  int sensor = analogRead(A0);
//  float tempC = (float)(sensor * (5.0 / 10.24));
  String tempC = "123456";
//  Serial.print(sensor);
  Serial.print("    temp: ");
  Serial.println(tempC);
  mySerial.println(tempC);
  mySerial.flush();
  }
  void Read(){
    while (Serial.available()){
      
      }
    }
