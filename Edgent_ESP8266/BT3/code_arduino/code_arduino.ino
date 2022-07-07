//int pin = A0;

void setup() {
//  pinMode(pin, INPUT); 
  Serial.begin(9600);
}
void loop() {
//  int sensor = analogRead(pin);
//  float voltage = (float)(sensor * (5.0 / 1024));
//  String tempC = String(voltage*100.0);
  String tempC = "30";
  Serial.println(tempC);
  delay(300);
}
