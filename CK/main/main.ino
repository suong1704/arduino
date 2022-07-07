#include <Servo.h>
#include <SoftwareSerial.h>
int echoPin = 7;
int trigPin = 8;
int servoPin = 9;
int duration; //micro second
float distance;
int pos=0;
Servo myServo;
unsigned long previousMillis = 0;
unsigned long openTime = 0;
int isOpen = 0;    // Trang thai thung rac (true: mo, false: dong)

SoftwareSerial sim800l(3, 2);
int ir_sensor = 5; //Chân cảm biến hồng ngoại nối chân số 5 Arduino
int value = 1;
// Đã gửi tin nhắn hay chưa
bool flag = false;

void setup() {

// initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  myServo.attach(servoPin);
  // Góc quay ban đầu của servo
  myServo.write(0);
  myServo.detach();

  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);   
  
  Serial.println("Initializing...");
  delay(1000);
  sim800l.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  sim800l.println("AT+CBC"); //Check whether it has registered in the network
  updateSerial();
  sim800l.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  sim800l.println("AT+COPS?"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  sim800l.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  
  sim800l.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

  pinMode(ir_sensor, INPUT);
}

void loop() {
  // Thời gian lấy mẫu của cảm biến siêu âm 100ms
  if((unsigned long) (millis() - previousMillis) >= 100){
    previousMillis = millis();

    distance = get_distance();
//    Serial.print("\nDistance in centimers: ");
//    Serial.print(distance);
    
    // Voi distance <= 15 mo thung rac
    if(distance <= 15){
      openTime = millis();
      open_dustbin();
      isOpen = 1;
      //Thoi gian mo thung rac la 4s
      delay(4000);
    }
  }

  // Khi thùng rác đầy thì gửi tin nhắn về điện thoại
  if(digitalRead(ir_sensor) == 0 && flag == false){
    Serial.println("Thung rac day");

    SendSMS();                          
    if (sim800l.available()){          
      Serial.write(sim800l.read()); 
    }
    updateSerial();
    //Da gui tin nhan
    flag = true;
  }
  if(digitalRead(ir_sensor) == 1 && flag == true){
    flag = false;
  }

  // Khi thoi gian mo lon hon 4s thi dong thung rac
  if ((millis() - openTime >= 4000) && (isOpen == true))
  {
    close_dustbin();
    isOpen = 0;
  }

  
}

void open_dustbin()
{
  myServo.attach(servoPin);
  Serial.println("\nmo thung rac");
  for (pos = 0; pos <= 90; pos += 1)   // Góc mở của servo (nắp thùng rác) từ 0-90
  {
    myServo.write(pos);                // yêu cầu servo chuyển đến vị trí trong biến 'pos'
    delay(5);                         // tốc độ mở thùng rác (cu 5 mili giay quay 1 goc 1 do)
  }
//  myServo.detach();
}
void close_dustbin()
{
//  myServo.attach(servoPin);
  Serial.println("\ndong thung rac");
  for (pos = 90; pos >= 0; pos -= 1)  
  {
    myServo.write(pos);              
    delay(5);                         
  }
  myServo.detach();
}

float get_distance(){
      // Sinh ra xung o chan trig
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    
    // Nhan 
    duration = pulseIn(echoPin,HIGH);
    distance = duration * 0.034/2.;
    return distance;
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800l.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim800l.available()) 
  {
    Serial.write(sim800l.read());//Forward what Software Serial received to Serial Port
  }
}

void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+84347570116\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("Thung rac da day!!! Hay di do rac");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);
}
