/*
 * Project TemperatureThing
 * Description:
 * Author:
 * Date:
 */
double temperatureC = 0.0;
int analogPin = A0;
void setup() {
  Serial.begin(9600);
  pinMode(analogPin, AN_INPUT);
}
void loop() {
  double voltage = analogRead(analogPin)/4095.0 * 3.3;
  temperatureC = 104.7*voltage - 53.1;
  Serial.println(temperatureC);
}