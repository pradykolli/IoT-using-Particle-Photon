/*
 * Project buzzLightyear
 * Description:
 * Author:
 * Date:
 */
const int buzzer = A5; //Piezo buzzer connected to an analog pin which supports pwm 
const int ditRedLED = D0; // LED for dit at digital D0 pin
const int dahGreenLED = D1; // LED for dah at digital D1 pin
const int sosSwitch = A0; //Sos Switch connected to analog pin A0

//Set up all the pins with theie respective modes.
// Also particle.function() to register the function that plays the message
void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(ditRedLED, OUTPUT);
  pinMode(dahGreenLED, OUTPUT);
  pinMode(sosSwitch,INPUT_PULLUP);
  Particle.function("playMessage",playMorseCode);
  Serial.println(9600);

}
// Looping the emergency morse code (SOS) sound if Switch is pressed
void loop(){
  // playMorseCode("PRADY"); 
  if(analogRead(sosSwitch) == LOW){
    playMorseCode("SOS");
    delay(1500);
  }       
}
// This method accepts a character as a parameter and calls appropriate function calls.
// playDit represents the Dit sound method
// playDah represents the Dah sound method
void playMorseLetter(char letter){
  if(letter == 'a' || letter == 'A'){
    playDit();
    playDah();
  }
  else if(letter == 'b' || letter == 'B'){
    playDah();
    playDit();
    playDit();
    playDit();

  }
  else if(letter == 'C' || letter == 'C'){
    playDah();
    playDit();
    playDah();
    playDit();
  }
  else if(letter == 'd' || letter == 'D'){
    playDah();
    playDit();    
    playDit();
  }
  else if(letter == 'e' || letter == 'E'){
    playDit();
  }
  else if(letter == 'f' || letter == 'F'){
    playDit();
    playDit();
    playDah();
    playDit();
  }
  else if(letter == 'g' || letter == 'G'){
    playDah();
    playDah();
    playDit();
  }
  else if(letter == 'h' || letter == 'H'){
    playDit();
    playDit();
    playDit();
    playDit();
  }
  else if(letter == 'i' || letter == 'I'){
    playDit();
    playDit();
  }
  else if(letter == 'j' || letter == 'J'){
    playDit();
    playDah();
    playDah();
    playDah();
  }
  else if(letter == 'k' || letter == 'K'){
    playDah();
    playDit();
    playDah();
  }
  else if(letter == 'l' || letter == 'L'){
    playDit();
    playDah();
    playDit();
    playDit();
  }
  else if(letter == 'm' || letter == 'M'){
    playDah();
    playDah();
  }
  else if(letter == 'n' || letter == 'N'){
    playDah();
    playDit();
    
  }
  else if(letter == 'o' || letter == 'O'){
    playDah();
    playDah();
    playDah();
  }
  else if(letter == 'p' || letter == 'P'){
    playDit();
    playDah();
    playDah();
    playDit();
  }
  else if(letter == 'q' || letter == 'Q'){
    playDah();
    playDah();  
    playDit();
    playDah();
  }
  else if(letter == 'r' || letter == 'R'){
    playDit();
    playDah();
    playDit();
  }
  else if(letter == 's' || letter == 'S'){
    playDit();
    playDit();
    playDit();
  }
  else if(letter == 't' || letter == 'T'){
    playDah();
  }
  else if(letter == 'u' || letter == 'U'){
    playDit();
    playDit();
    playDah();
  }
  else if(letter == 'v' || letter == 'V'){
    playDit();
    playDit();
    playDit();
    playDah();
  }
  else if(letter == 'w' || letter == 'W'){
    playDit();
    playDah();
    playDah();
  }
  else if(letter == 'x' || letter == 'X'){
    playDah();
    playDit();
    playDah();
    playDit();
  }
  else if(letter == 'y' || letter == 'Y'){
    playDah();
    playDit();
    playDah();
    playDah();
  }
  else if(letter == 'z' || letter == 'Z'){
    playDah();
    playDah();
    playDit();
    playDit();
  }
  else{ //If space or special character comes into picture.
    letterEnds();
  }
}
// This method accepts a String as a message which will be passed from the webpage and iterates through
//  the string and plays the morse code for each character. This returns a integer value 200.
int playMorseCode(String message){
  std::string str(message);
  Serial.println(message);
  for (unsigned int i = 0; i < str.size(); i++){
    playMorseLetter(str[i]);
    letterEnds();
  }
  return 200;
}
// Scale 1 unit == 50 milli seconds.
//       3 units == 150 milli seconds.
// This function plays the Dit sound for 50 milli seconds and a gap of 50 milli seconds when called.  
void playDit(){
    analogWrite(buzzer,128,440);
    digitalWrite(ditRedLED,HIGH);
    delay(50);
    analogWrite(buzzer,0,440);
    digitalWrite(ditRedLED,LOW);
    delay(50);
}
// Scale 1 unit == 50 milli seconds.
//       3 units == 150 milli seconds.
// This function plays the Dah sound for 150 milli seconds and a gap of 50 milli seconds when called.  
void playDah(){
    analogWrite(buzzer,128,440);
    digitalWrite(dahGreenLED,HIGH);
    delay(150);
    analogWrite(buzzer,0,440);
    digitalWrite(dahGreenLED,LOW);
    delay(50);
}
// Scale 1 unit == 50 milli seconds.
//       3 units == 150 milli seconds.
// This function pauses the sound for 150 milli seconds when called.  
void letterEnds(){
    analogWrite(buzzer,0,440);
    delay(150);
}