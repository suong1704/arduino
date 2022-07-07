void setup() {
pinMode(12, OUTPUT); //sensor
//pinMode(9, OUTPUT); //red
Serial.begin(9600);
}
void loop() {
//int sensor = analogRead(A0);
//float tempC = (float)(sensor * (5.0 / 10.24));
////float tempC = (voltage - .5) * 100;
////float tempF = (tempC * 1.8) + 32;
//Serial.print(sensor);
//Serial.print("    temp: ");
//Serial.println(tempC);
//if (tempC > 24.0) { 
  digitalWrite(12, HIGH);
  Serial.print("1");
  delay(1000);
  digitalWrite(12, LOW);
  Serial.print("2");
  delay(1000);
//}
//else{
//  digitalWrite(13, LOW);
//}
//analogWrite(9, sensor/4);
//

//delay(100);
}
