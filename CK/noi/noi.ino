
#include <SoftwareSerial.h>
#include "Adafruit_BMP085.h"
#define SIM800_TX_PIN 8
#define SIM800_RX_PIN 9
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN); //Create software serial object to communicate with GSM Module

#define IN1 4  //motor bom
#define IN2 5  //motor bom

#define IN3 7  //motor hut
#define IN4 6  //motor hut

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

Adafruit_BMP085 bmp;

double press = 0.0;
double water_height = 0;
double temp = 0.0;
int index = 0;
String number = "";
String message = "";
String statebom = "off";
String statehut = "off";

char incomingByte;
String incomingData;
bool atCommand = true;

void setup()
{
  Serial.begin(9600); 
  mySerial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("Khong tim thay cam bien BMP085, kiem tra ket noi");
    while (1) {}
  }
  while (!mySerial.available()) {
    mySerial.println("AT");
    delay(1000);
    Serial.println("connecting....");
  }
  Serial.println("Connected..");
  mySerial.println("AT+CMGF=1");  
  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0,0"); 
  delay(1000);
  mySerial.println("AT+CMGL=\"REC UNREAD\""); 
  Serial.println("Ready to received Commands..");

  pinMode(IN1, OUTPUT);   //bom
  pinMode(IN2, OUTPUT);   //bom

  pinMode(IN3, OUTPUT);   //hut
  pinMode(IN4, OUTPUT);   //hut
}

void loop()
{
  press = bmp.readPressure();
  water_height = ((press-99720)*0.01023478599);
  temp = bmp.readTemperature();
//  Serial.println(temp);
  if (mySerial.available()) {
    delay(100);
    while (mySerial.available()) {
      incomingByte = mySerial.read();
      incomingData += incomingByte;
    }
    delay(10);
    if (atCommand == false) {
      receivedMessage(incomingData);
    } else {
      atCommand = false;
    }
    if (incomingData.indexOf("OK") == -1) {
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      atCommand = true;
    }
    incomingData = "";
  }
  send_data(press, water_height, temp);
  delay(1000);
}

void Bom(int speed) { 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 255 - speed);
//  statebom = "running at speed "+ String(speed);
  statebom="on";
}

void Hut(int speed) { 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN3, HIGH);
  analogWrite(IN4, 255 - speed);
//  statehut = "running at speed "+ String(speed);
  statehut="on";
}

void DungBom() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  statebom = "off";
}

void DungHut() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  statehut = "off";
}

void StateBom(){
   String message = "motor bom is " + statebom;
   sendSMS(message);
}
void StateHut(){
   String message = "motor hut is " + statehut;
   sendSMS(message);
}

void Water(){
   sendSMS(String(water_height));
}
void Temp(){
   sendSMS(String(temp));
}

void sendSMS(String msg)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+84932427501\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(msg);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void receivedMessage(String inputString) {

  index = inputString.indexOf('"') + 1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0, index);
  Serial.println("Number: " + number);

  index = inputString.indexOf("\n") + 1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
  message.toUpperCase(); 
  
  if(message.indexOf("B1")>=0){
      Bom(60);
  }
  if(message.indexOf("B2")>=0){
      Bom(120);
  }
  if(message.indexOf("B3")>=0){
      Bom(180);
  }
  if(message.indexOf("H1")>=0){
      Hut(60);
  }
  if(message.indexOf("H2")>=0){
      Hut(120);
  }
  if(message.indexOf("H3")>=0){
      Hut(180);
  }
   if(message.indexOf("DB")>=0){
     DungBom();
   }
  
   if(message.indexOf("DH")>=0){
     DungHut();
   }
   if(message.indexOf("SB")>=0){
       StateBom();
   }
   if(message.indexOf("SH")>=0){
       StateHut();
   }
   if(message.indexOf("W")>=0){
       Water();
   }
   if(message.indexOf("T")>=0){
       Temp();
   }
}

void send_data(double press, double water_height, double temp) {
//   mySerial.println("AT"); //Check state of module
  delay(500);
  mySerial.println("AT+CPIN?"); //Check sim ok: READY
  delay(500);
 
  mySerial.println("AT+CREG?"); //Check if connect to GSM [0/1]
  delay(500);
 
  mySerial.println("AT+CGATT?"); //Error or not
  delay(500);
 
  mySerial.println("AT+CIPMUX=0"); //1 connection
  delay(2000);

  mySerial.println("AT+CSTT=\"VIETTEL EMAIL\"");//start task and setting the APN,
  delay(1000);

  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);

 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
//  GET https://api.thingspeak.com/update?api_key=6TLCLM7PLVJCDECS&field1=0
  String str_press="GET https://api.thingspeak.com/update?api_key=6TLCLM7PLVJCDECS&field1=" + String(press);
  String str_temp = "GET https://api.thingspeak.com/update?api_key=H7N6M44CZS7L1YSU&field1=" + String(temp);
  String str_level = "GET https://api.thingspeak.com/update?api_key=CKIF3WE5CHEEQQ0L&field1=" + String(water_height);
  Serial.println(str_press);
  Serial.println(str_temp);
  Serial.println(str_level);
  mySerial.println(str_press);//begin send data to remote server
  mySerial.println(str_temp);
  mySerial.println(str_level);
  
  delay(4000);
 
  mySerial.println((char)26);//sending
  delay(15000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
//  ShowSerialData();
  
   
}
