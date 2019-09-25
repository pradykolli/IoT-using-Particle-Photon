/*
 * Project InitialPhotonFlash
 * Description:
 * Author:
 * Date:
 */

void flashD7(double onTime, double offTime){
  digitalWrite(D7,HIGH);
  delay(onTime);
  digitalWrite(D7,LOW);
  delay(offTime);
}
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D7,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  int r = random(500,1500);
  flashD7(r,500);
  // The core of your code will likely live here.

}