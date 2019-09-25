/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/s533625/Documents/GitHub/IoT/charToD7/src/charToD7.ino"
/*
 * Project charToD7
 * Description:
 * Author:
 * Date:
 */
void flashD7(double onTime, double offTime);
void setup();
void loop();
#line 7 "c:/Users/s533625/Documents/GitHub/IoT/charToD7/src/charToD7.ino"
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
  // The core of your code will likely live here.
  String name = "Pradeep";
  for(int i = 0; i< name.length(); i++){
    int asciiChar = int(name[i]);
    int total = ( 2 * asciiChar ) + 100;
    flashD7(total,500);
  }
}