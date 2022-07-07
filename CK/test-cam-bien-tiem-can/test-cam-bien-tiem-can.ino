#include <Servo.h>
int echoPin = 7;
int trigPin = 8;
int servoPin = 2;
int duration; //micro second
float distance;
int pos=0;
Servo myServo;
volatile int trangthai = LOW;
// Trang thai thung rac (1: mo, 0: dong)
volatile int isOpen = 0;

void setup() {

// initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(2,LOW);
  attachInterrupt(0,doctrangthai,CHANGE);
  myServo.attach(servoPin);
  // Goc quay ban dau cua servo
  myServo.write(0);
}

void loop() {
  distance = read_distance(trangthai);
  open_dustbin(distance)
}
int read_distance(int trangthai){
    digitalWrite(trigPin,LOW);
    digitalWrite(trigPin,HIGH);
    digitalWrite(trigPin,LOW);
    
    // Nhan 
    duration = pulseIn(echoPin,trangthai);
    distance = duration * 0.034/2.;
    Serial.print("\nDistance in centimers: ");
    Serial.print(distance);
    delay(4000);
    return distance;
  }
void open_dustbin(int distance)
{
  if (distance <= 15){
    Serial.println("\nMo thung rac");
    for (pos = 0; pos <= 90; pos += 1)   
    {
      myServo.write(pos);                
      delay(5);                         
    }
    isOpen = 1;
    delay(4000)
    Serial.println("\nDong thung rac");
    for (pos = 90; pos >= 0; pos -= 1)  
    {
      myServo.write(pos);              
      delay(10);                         
    }
    isOpen = 0;
  }
}
void doctrangthai(int isOpen){
  if (isOpen == 0 ){trangthai=HIGH;}
  else {trangthai=LOW;}
 }
void close_dustbin(int isOpen)
{
  if(isOpen == 0){
    Serial.println("\nDong thung rac");
  for (pos = 90; pos >= 0; pos -= 1)  
  {
    myServo.write(pos);              
    delay(10);                         
  }
    }

}
