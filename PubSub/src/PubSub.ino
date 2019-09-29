/*
 * Project PubSub
 * Description:
 * Author:
 * Date:
 */
const int switchy = A0;
const int led = D7;
int luckyNumber;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(switchy,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  Particle.subscribe("tapped",handleTap,MY_DEVICES);
  Particle.variable("luckyNumber",luckyNumber);
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(digitalRead(switchy) == LOW){
    luckyNumber = random(100);
    Particle.publish("tapped", String::format("%d",luckyNumber),PRIVATE);
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
    
  }

}

void handleTap(String event, String data){
  Serial.println(data);
}