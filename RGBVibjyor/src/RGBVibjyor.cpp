/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/s533625/Documents/GitHub/IoT/RGBVibjyor/src/RGBVibjyor.ino"
/*
 * Project RGBVibjyor
 * Description:
 * Author:
 * Date:
 */

// setup() runs once, when the device is first turned on.
void setup();
void showRainbow();
void runColors();
void loop();
#line 9 "c:/Users/s533625/Documents/GitHub/IoT/RGBVibjyor/src/RGBVibjyor.ino"
void setup() {
  // Put initialization like pinMode and begin functions here.

}
void showRainbow(){
  RGB.control(true);
  Serial.println(RGB.controlled());
  // VIBGYOR COLORS
  RGB.color(148, 0, 211);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(75, 0, 130);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(0, 0, 255);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(0, 255, 0);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(255, 255, 0);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(255, 127, 0);
  delay(1000);
  RGB.brightness(255);
  delay(1000);

  RGB.color(255, 0, 0);
  delay(1000);
  RGB.brightness(255);
  delay(1000);
  // resume normal operation
  RGB.control(false);


}

void runColors(){
  for(int i = 0; i <= 255; i++){
    for(int j = 0 ; j <= 255; j++){
      for(int k = 0; k <= 255; k++ ){
        RGB.control(true);
        Serial.println(RGB.controlled());
        RGB.color(i, j, k);
        delay(100);
        RGB.control(false);

      }
    }
  }
}
// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  showRainbow();
  delay(2000);
  runColors();
}