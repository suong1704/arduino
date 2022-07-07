const int hot = 27; //set hot parameter
const int cold = 21; //set cold parameter
int pin = A0;
int led1 = 6;
int led2 = 9;
int led3 = 11;

void setup() {
pinMode(pin, INPUT); //sensor
pinMode(led1, OUTPUT); //blue
pinMode(led2, OUTPUT); //green
pinMode(led3, OUTPUT); //red
Serial.begin(9600);
}
void loop() {
int sensor = analogRead(pin);
float voltage = (float)(sensor * (5.0 / 1024));
/* 1024 - 5V
 *  a   - ?V
 */
float tempC = voltage*100.0;
/* 0 - 5V
 * 0 - 100 do C
 */
Serial.print("temp: ");
Serial.println(tempC);
if (tempC < cold) { //cold
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
else if (tempC >= hot) { //hot
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
}
else { //fine
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
}
delay(10);
}
