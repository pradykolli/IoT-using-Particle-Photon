/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/s533625/Documents/GitHub/IoT/increment100ms/src/increment100ms.ino"
/*
 * Project increment100ms
 * Description:
 * Author:
 * Date:
 */
void flashD7(double onTime, double offTime);
void setup();
void loop();
#line 7 "c:/Users/s533625/Documents/GitHub/IoT/increment100ms/src/increment100ms.ino"
int count;
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
  count = 100;
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  while(count<600){
    count += 100;
    flashD7(count,500);
  }

}