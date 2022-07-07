#include <Servo.h>
int echoPin = 7;
int trigPin = 8;
int servoPin = 9;
int duration; //micro second
float distance;
int pos=0;
Servo myServo;

unsigned long previousMillis = 0;
unsigned long openTime = 0;

// Trang thai thung rac (1: mo, 0: dong)
int isOpen = 0;

void setup() {

// initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  myServo.attach(servoPin);
  // Goc quay ban dau cua servo
  myServo.write(0);
}

void loop() {
  // Thời gian lấy mẫu của cảm biến siêu âm 100ms
  if((unsigned long) (millis() - previousMillis) >= 100){
    previousMillis = millis();
    // Sinh ra xung o chan trig
    digitalWrite(trigPin,LOW);
    digitalWrite(trigPin,HIGH);
    digitalWrite(trigPin,LOW);
    
    // Nhan 
    duration = pulseIn(echoPin,HIGH);
    distance = duration * 0.034/2.;
    Serial.print("\nDistance in centimers: ");
    Serial.print(distance);

    // Voi distance <= 15 mo thung rac
    if(distance <= 15){
      openTime = millis();
      open_dustbin();
      isOpen = 1;
      //Thoi gian mo thung rac la 4s
      delay(4000);
    }
  }


  // Khi thoi gian mo lon hon 4s thi dong thung rac
  if ((millis() - openTime >= 4000) && (isOpen == 1))
  {
    close_dustbin();
    isOpen = 0;
  }
}

void open_dustbin()
{
  Serial.println("\nMo thung rac");
  for (pos = 0; pos <= 90; pos += 1)   
  {
    myServo.write(pos);                
    delay(5);                         
  }
}
void close_dustbin()
{
  Serial.println("\nDong thung rac");
  for (pos = 90; pos >= 0; pos -= 1)  
  {
    myServo.write(pos);              
    delay(10);                         
  }

}
