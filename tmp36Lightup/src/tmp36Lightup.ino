/*
 * Project tmp36Lightup
 * Description:
 * Author:
 * Date:
 */
int const cold = D0; // blue LED
int const justRight = D1; // yellow LED
int const hot = D2; //green LED
int const testLED = A0; //switch 1
int const capture = A1; //switch 2
int const tmp36 = A2; // tmp36 sensor
double temperatureC = 0.0; //Recorded temperature
double ambientTemp; // Ambient temperature 

// setup() runs once, when the device is first turned on.
// In this setup we capture the initial temperature and set pinmodes of analogue and digital IO's.
// We set the ambient temperature as the temperature that is captured on bootup of firmware.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  pinMode(cold,OUTPUT);
  pinMode(justRight,OUTPUT);
  pinMode(hot,OUTPUT);
  pinMode(tmp36, AN_INPUT);
  pinMode(testLED,INPUT_PULLUP);
  pinMode(capture,INPUT_PULLUP);
  double voltage = analogRead(tmp36)/4095.0 * 3.3;
  temperatureC = 104.7*voltage - 53.1;
  ambientTemp = temperatureC;
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  // If switch 1 is pressed it will glow all the led's in sequence for 50 milli seconds each 
  if (digitalRead(testLED) == LOW){
    digitalWrite(cold,HIGH);
    delay(50);
    digitalWrite(cold,LOW);
    delay(50);
    digitalWrite(justRight,HIGH);
    delay(50);
    digitalWrite(justRight,LOW);
    delay(50);
    digitalWrite(hot,HIGH);
    delay(50);
    digitalWrite(hot,LOW);
    delay(50);
  }
  // If switch 2 is pressed based on the temperature the led associated will light up.
  // If the captured temperature is 2 degrees less than the ambient temperature the blue(COLD) LED lights up.
  // If the captured temperature is 2 degrees more than the ambient temperature the green(HOT) LED lights up.
  // Else the ambient temperature, the yellow LED lights up.
  else if (digitalRead(capture) == LOW){
    digitalWrite(cold,LOW);
    digitalWrite(hot,LOW);
    digitalWrite(justRight,LOW);
    double voltage = analogRead(tmp36)/4095.0 * 3.3;
    temperatureC = 104.7*voltage - 53.1;
    Serial.println("ambientTemp");
    Serial.println(ambientTemp);
    Serial.println("temperatureC");
    Serial.println(temperatureC);
    if(temperatureC < ambientTemp - 2.0){
      digitalWrite(cold,HIGH);
      digitalWrite(hot,LOW);
      digitalWrite(justRight,LOW);
      delay(1000);
    }
    else if(temperatureC > ambientTemp + 2.0){
      digitalWrite(hot,HIGH);
      digitalWrite(cold,LOW);
      digitalWrite(justRight,LOW);
      delay(1000);
    }
    else{
      digitalWrite(justRight,HIGH);
      digitalWrite(hot,LOW);
      digitalWrite(cold,LOW);
      delay(1000);
    }
  }
  
}

