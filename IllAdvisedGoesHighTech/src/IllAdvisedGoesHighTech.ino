/*
 * Project IllAdvisedGoesHighTech
 * Description:
 * Author:
 * Date:
 */

#include <math.h>
#include <SparkFunMicroOLED.h>


int const button = A0; //  Switch in our case button  

float temperatureInF = 0.0; //temperature in F
String tempInF;
String bcRateStr;
float windspeed = 0.0; // wind speed 
float windChill = 0.0; // wind chill variable

float bcRate = 0.0; // bitcoin rate
float bcValues[3]; //bitcoin array
String status; //Status -> Rising Falling Neither
// Timer timer(60000, publishTempNbcRate); // Timer to call function every minute (60000 ms).
MicroOLED oled;
// publishing the temperature and bitcoin rate to particle
// void publishTempNbcRate(){
//   Particle.publish("tempInF");
//   Particle.publish("bcRate");
//   decision();
// }

// Calculating wind chill.
float calculateWindChill(float airTemperature, float windSpeedInMPH){
  float powerVariable = pow(windSpeedInMPH,0.16);
  windChill = 35.74 + (0.6215 * airTemperature) - (35.75 * powerVariable) + (0.4275 * airTemperature * powerVariable);
  Serial.println("windchill");
  Serial.println(windChill);
  return windChill;
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
void displayArrow(){
  if(status == "Falling"){
    oled.line(32,40,28,36);
    oled.line(32,40,36,36);
    oled.lineV(32,24,16);
  }
  else if(status == "Rising"){
    oled.line(32,24,28,28);
    oled.line(32,24,36,28);
    oled.lineV(32,24,16);
  }
  else{
    oled.line(32,40,28,36);
    oled.line(32,40,36,36);
    oled.lineV(32,24,16);
    oled.line(32,24,28,28);
    oled.line(32,24,36,28);
    oled.lineV(40,24,16);
  }
}
// This function plays the ascending notes sound for 100 milli seconds and a glows green led for 200milliseconds.  
void investInBC(){
  Serial.println("Decision: Invest");
  oled.setFontType(0);  // Set font to type 1
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  // Print can be used to print a string to the screen:
  oled.print("wind chill:");
  oled.println(windChill);
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
        // Refresh the display
  for (int i=0 ; i<3; i++){
    oled.println(bcValues[i]);
  }
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  oled.println("Invest");
  displayArrow();
  oled.display(); 
  delay(5000); 
}

// This function plays the descending notes sound for 100 milli seconds and a glows red led for 200milliseconds.  
void dontInvestInBC(){
  Serial.println("Decision: Do not Invest"); 
  oled.setFontType(0);  // Set font to type 1
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  // Print can be used to print a string to the screen:
  oled.print("wind chill:");
  oled.println(windChill);
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
        // Refresh the display
  for (int i=0 ; i<3; i++){
    oled.println(bcValues[i]);
  }
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  oled.println("Do not Invest");
  displayArrow();
  oled.display(); 
  delay(5000);  
}

// This function plays the same frequency notes sound for 100 milli seconds and a glows yellow led for 200milliseconds.  
void flipACoin(){
  oled.setFontType(0);  // Set font to type 1
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  // Print can be used to print a string to the screen:
  oled.print("wind chill:");
  oled.println(windChill);
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
        // Refresh the display
  for (int i=0 ; i<3; i++){
    oled.println(bcValues[i]);
  }
  oled.display(); 
  delay(5000);
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 0); // Set cursor to top-left
  oled.println("Flip a coin");
  displayArrow();
  oled.display(); 
  delay(5000); 
  Serial.println("Decision: Flip a coin");
}

// this function swaps the values in bitcoinValues array
void swapValues(float &a, float &b){
  double temp = a;
  a = b;
  b = temp;
}

//Array to hold and shift bit coin prices. 
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

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  pinMode(button,INPUT_PULLUP);
  // Put initialization like pinMode and begin functions here.
  Particle.subscribe("hook-response/tempInF", fetchTempWind, MY_DEVICES);
  Particle.subscribe("hook-response/bcRate", getCoinRate, MY_DEVICES);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
 // Get some data
    String data = String(10);
    // Trigger the integration
    Particle.publish("bcRate", data, PRIVATE);

    String data2 = String(10);
    // Trigger the integration
    Particle.publish("tempInF", data2, PRIVATE);
    // Wait 60 seconds
    decision();
    // Serial.println(decision());
    String data3 = String::format("WindChill:  %.2f ", windChill) + " Decision: " + status ;
    Serial.println(data3);
    delay(60000);

}