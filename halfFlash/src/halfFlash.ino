/*
 * Project halfFlash
 * Description:
 * Author:
 * Date:
 */
const int led = D0;
int brightness = 128;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led,OUTPUT);
  analogWrite(led,brightness,1);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}