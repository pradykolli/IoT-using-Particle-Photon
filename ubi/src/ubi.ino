/*
 * Project ubi
 * Description:
 * Author:
 * Date:
 */
// This example sends data to multiple variables to 
// Ubidots through TCP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

#ifndef UBIDOTS_TOKEN
#define UBIDOTS_TOKEN "BBFF-n4xL2rARPhcorBk1TAIsKPP5hvtFEF"  // Put here your Ubidots TOKEN
#endif

// Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP);
Ubidots ubidots(UBIDOTS_TOKEN, UBI_EDUCATIONAL, UBI_TCP);// Replace the above line if you're an Ubidots for Education user.

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions


/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.setDebug(true);
  pinMode(D7,OUTPUT);
  //ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  float value1 = analogRead(A0);
  float value2 = analogRead(A1);
  float value3 = analogRead(A2);
  ubidots.add("Variable_Name_One", value1);  // Change for your variable name
  ubidots.add("Variable_Name_Two", value2);
  ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if(bufferSent){
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }
  digitalWrite(D7,HIGH);
  delay(5000);
}