/*
 * Project switchy
 * Description:
 * Author:
 * Date:
 */
const int led = D4;
const int switchy = D6;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led,OUTPUT);
  pinMode(switchy,INPUT_PULLUP);
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(digitalRead(switchy) == LOW){
    digitalWrite(led, HIGH);
    Serial.println("Mini me is here.");
    delay(1000);


    
  }
  else{
    digitalWrite(led,LOW);
  }
}