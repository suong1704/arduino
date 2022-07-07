
int pin = A0;

void setup() {
pinMode(pin, INPUT); 
Serial.begin(9600);
}
void loop() {
  int sensor = analogRead(pin);
  float voltage = (float)(sensor * (5.0 / 1024));
  float tempC = voltage*100.0;
  Serial.print(String(tempC));
  delay(1000);
  
}
