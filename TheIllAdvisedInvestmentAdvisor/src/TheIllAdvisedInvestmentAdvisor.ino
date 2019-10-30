/*
 * Project TheIllAdvisedInvestmentAdvisor
 * Description:
 * Author: Pradeep Kolli
 * Date:
 */
#include "math.h"
int const redLed = D0; // Red led
int const yellowLed = D1; //Yellow Led
int const greenLed = D2; //green Led
int const speaker = A5; // Piezo Buzzer
int const button = A0; //  Switch in our case button  

float temperatureInF = 0.0; //temperature in F
float windspeed = 0.0; // wind speed 
float windChill = 0.0; // wind chill variable

float bcRate = 0.0; // bitcoin rate
float bcValues[3]; //bitcoin array
String status; //Status -> Rising Falling Neither
Timer timer(60000, publishTempNbcRate); // Timer to call function every minute (60000 ms).

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  Particle.subscribe("hook-response/bcRate", getCoinRate, MY_DEVICES);
  Particle.subscribe("hook-response/tempInF", fetchTempWind, MY_DEVICES);
  pinMode(redLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(speaker,OUTPUT);
  pinMode(button,INPUT_PULLUP);

  timer.start();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  if (digitalRead(button) == LOW)
  {
    Serial.print("buttonPressed");
    String data = String::format("WindChill:  %.2f ", windChill) + " Decision: " + status ;
    Serial.println(data);
    Particle.publish("GoogleDocsXL",data);
  }
}

// This function plays the ascending notes sound for 100 milli seconds and a glows green led for 200milliseconds.  
void investInBC(){
    digitalWrite(greenLed,HIGH);
    analogWrite(speaker,128,440);
    delay(100);
    analogWrite(speaker,0,440);
    analogWrite(speaker,128,550);
    delay(100);
    analogWrite(speaker,0,440);
    analogWrite(speaker,128,660);
    delay(100);
    analogWrite(speaker,0,440);
    digitalWrite(greenLed,LOW);
    delay(200);
}

// This function plays the descending notes sound for 100 milli seconds and a glows red led for 200milliseconds.  
void dontInvestInBC(){
    digitalWrite(redLed,HIGH);
    analogWrite(speaker,128,660);
    delay(100);
    analogWrite(speaker,0,440);
    analogWrite(speaker,128,550);
    delay(100);
    analogWrite(speaker,0,440);
    analogWrite(speaker,128,440);
    delay(100);
    analogWrite(speaker,0,440);
    digitalWrite(redLed,LOW);
    delay(200);
}

// This function plays the same frequency notes sound for 100 milli seconds and a glows yellow led for 200milliseconds.  
void flipACoin(){
    digitalWrite(yellowLed,HIGH);
    playNeutralSound();
    playNeutralSound();
    playNeutralSound();
    digitalWrite(yellowLed,LOW);
    delay(200);
}

// This function plays the same frequency sound when called.  
void playNeutralSound(){
  analogWrite(speaker,128,440);
  delay(100);
  analogWrite(speaker,0,440);
  delay(100);
}

// This is our decision maker functionality which tells us to invest or to not invest in bitcoin 
String decision(){
  behaviour();
  if(windChill < 50 && status == "Rising"){
    dontInvestInBC();
    return "Do not invest folks!";
  }
  else if (windChill < 50 && status == "Falling"){
    investInBC();
    return "Do invest folks!";
  }
  else if(windChill < 50 && status == "Neither"){
    flipACoin();
    return "Flip a coin buddy!";
  }
  else if(windChill >= 50 && status == "Rising"){
    investInBC();
    return "Do invest folks!";
  }
  else if (windChill >=50 && status == "Falling"){
    dontInvestInBC();
    return "Do not invest folks!";
  }
  else if(windChill >= 50 && status == "Neither"){
    flipACoin();
    return "Flip a coin buddy!";
  }
  return "";
}

// Calculating wind chill.
float calculateWindChill(float airTemperature, float windSpeedInMPH){
  float powerVariable = pow(windSpeedInMPH,0.16);
  windChill = 35.74 + (0.6215 * airTemperature) - (35.75 * powerVariable) + (0.4275 * airTemperature * powerVariable);
  return windChill;
}

// publishing the temperature and bitcoin rate to particle
void publishTempNbcRate(){
    Particle.publish("tempInF");
    Particle.publish("bcRate");
    String dec = decision();
    Serial.println("publishTempNbcRate");
    Serial.println(dec);

}

// Fetch temperature from webhook and calculate windchill
void fetchTempWind(String event,String temperature){
  Serial.println("fetchdTemp");
  Serial.println(temperature);
  temperatureInF = temperature.substring(0, temperature.indexOf(",")).toFloat();
  windspeed = temperature.substring(temperature.indexOf(",") + 1, temperature.length()).toFloat();
  temperatureInF = ((9 / 5) * (temperatureInF - 273.15)) + 32; //Temperature in F
  windspeed = 2.23694 * windspeed; // wind speed in mph
  calculateWindChill(temperatureInF,windspeed);
}

// since {{{bpi.usd.rate}}} gives a string data like 8,331.9700 we need to convert this into actual float value.
void getCoinRate(String event,String bitcoininString){
  Serial.println("fetchdBC");
  Serial.println(bitcoininString);
  bitcoininString.replace(",", "");
  bcRate = bitcoininString.toFloat();
}

// Storing the new value of bitcoin in array and pushing the next to other positions

void bitCoinArray(double coin_rate)
{
  if (bcValues[2] == 0.0)
  {
    bcValues[2] = coin_rate;
  }
  else
  {
    for (int i = 0; i < 3; i++)
    {
      if (i == 2)
      {
        bcValues[2] = coin_rate;
      }
      else
      {
        swapValues(bcValues[i], bcValues[i + 1]);
      }
    }
  }
}


// this function swaps the values in bitcoinValues array

void swapValues(float &a, float &b){
  double temp = a;
  a = b;
  b = temp;
}


// behaviour function compares the values and sets the status as the bitcoin behaviour string.
void behaviour()
{
  bitCoinArray(bcRate);
  for (int i = 0; i < 3; i++){
    Serial.println(bcValues[i]);
  }
  if (bcValues[1] > bcValues[0] && bcValues[2] > bcValues[1]){
    status =  "Rising";
  }
  else if (bcValues[1] < bcValues[0] && bcValues[2] < bcValues[1]){
    status =  "Falling";
  }
  else{
    status =  "Neither";
  }
}