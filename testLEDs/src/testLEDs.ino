/*
 * Project testLEDs
 * Description:
 * Author:
 * Date:
 */

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  digitalWrite(D0,HIGH);
  delay(1000);
  digitalWrite(D0,LOW);
  delay(200);
  digitalWrite(D1,HIGH);
  delay(1000);
  digitalWrite(D1,LOW);
  delay(200);
  
}