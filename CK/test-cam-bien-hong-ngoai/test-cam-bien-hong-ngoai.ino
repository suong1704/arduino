int ir_sensor = 5; //Chân cảm biến nối chân số 5 Arduino
int value;

void setup() 
{
  Serial.begin(9600);

  pinMode(ir_sensor, INPUT);

}

void loop() 
{
  value = digitalRead(ir_sensor); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
  // Điều chỉnh giá trị cảm biến(xoay biến trở) để thay đổi thay đổi khoảng cách xác nhận rác đầy (khoảng 4cm)
  Serial.println(value);
  
  if(value == 0){
    Serial.println("Thung rac day");
  }
  delay(200);

}
