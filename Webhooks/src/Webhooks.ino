/*
 * Project Webhooks
 * Description:
 * Author:
 * Date:
 */

const int switchy = A0;
const int minTemp = 0;
const int maxTemp = 100;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(switchy, INPUT_PULLUP);
  pinMode(D7,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(digitalRead(switchy) == LOW){
    int temperature = random(minTemp,maxTemp);
    Particle.publish("tempertemper", String::format("%d",temperature));
    digitalWrite(D7,HIGH);
    delay(500);
    digitalWrite(D7,LOW);
  }
}