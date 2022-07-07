#include <SoftwareSerial.h>

SoftwareSerial sim800l(3, 2);

int ir_sensor = 5; //Chân cảm biến nối chân số 5 Arduino
int value = 1;
int count = false;
void setup() 
{
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

void loop() 
{
  value = digitalRead(ir_sensor); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
  // Điều chỉnh giá trị cảm biến(xoay biến trở) để thay đổi thay đổi khoảng cách xác nhận rác đầy (khoảng 4cm)
  Serial.println(value);
  if (value ==1 ){ count = true}
  if(value == 0 && count == false){
    count = true;
    Serial.println("Thung rac day");

    SendSMS();                          //And this function is called
    if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
      Serial.write(sim800l.read()); 
    }
    updateSerial();

  }
  delay(200);

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
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mod e
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
