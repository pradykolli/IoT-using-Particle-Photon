/*
 * Project gcp
 * Description:
 * Author:
 * Date:
 */

const int led = D7;
const int publishInterval = 12000;
int timesCalled = 0;
int randomNum;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  digitalWrite(led, HIGH);
  delay(publishInterval/2);
  digitalWrite(led,LOW);
  delay(publishInterval/2);
  timesCalled++;
  randomNum = random();
  String data = String::format("{\"nuTimes\" : %d, \"randomNum\": %d}",timesCalled,randomNum);

  Particle.publish("mygcp", data, PRIVATE);
}
