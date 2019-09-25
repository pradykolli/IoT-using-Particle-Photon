/*
 * Project IinIOT
 * Description:
 * Author:
 * Date:
 */
int blueLED = D7;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(blueLED,INPUT);
  Particle.function("fireItUp",turnOn);
  Particle.function("shutItDown",turnOff);
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

int turnOn(String message){
  digitalWrite(blueLED,HIGH);
  Serial.println("Turned On");
  Serial.println(message);
  return 0;
}
int turnOff(String message){
  digitalWrite(blueLED,LOW);
  Serial.println("Turned Off");
  Serial.println(message);
  return 0;
}