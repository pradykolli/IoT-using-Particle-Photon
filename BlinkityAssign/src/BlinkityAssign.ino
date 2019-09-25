/*
 * Project BlinkityBlink
 * Description:
 * Author:
 * Date:
 */
const int switchy0 = A0;
const int switchy1 = A1;
const int led0 = D0;
const int led1 = D1;
const int led2 = D2;
int initalValue = 0;
int x =0,y=0,z=0;
bool reverseDirection = false;
void decToBin(int n) 
{ 
	int a[3], i;    

  // for(i=0; n>0; i++){        
  //   a[i]=n%2;    
  //   n= n/2; 
  // } 
  for (int i = 2; i >= 0; i--) { 
        int k = n >> i; 
        if (k & 1) 
            a[i] = 1; 
        else
            a[i] = 0; 
    } 

  x = a[2];
  y = a[1];
  z = a[0];
  

  // printf("%d,%d,%d",x,y,z);
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led0,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(switchy0,INPUT_PULLUP);
  pinMode(switchy1,INPUT_PULLUP);
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(digitalRead(switchy0) == LOW){
    Serial.println("inside a0");
    if(initalValue < 8 && initalValue >=0){
      Serial.println(initalValue);
      Serial.println(reverseDirection);
      decToBin(initalValue);
      if(x==1){
        digitalWrite(led0,HIGH);
      } 
      else if(x == 0){
        digitalWrite(led0,LOW);
      }
      if(y==1){
        digitalWrite(led1,HIGH);
      } 
      else if(y==0){
        digitalWrite(led1,LOW);
      }
    if(z==1){ 
      digitalWrite(led2,HIGH);
      }
      else if(z==0){
        digitalWrite(led2,LOW);
      } 
      delay(1000);
      if (reverseDirection){
        initalValue -= 1;
      }
      else if(!reverseDirection){
        initalValue += 1;
      }
      Serial.println("after increment or decrement");
      Serial.println(initalValue);
    }
    else if(initalValue < 0){ 
      initalValue = 7;
    }
    else{
      initalValue = 0;
      digitalWrite(led0,LOW);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
    }
  }
  else if(digitalRead(switchy1) == LOW){
    digitalWrite(led0,LOW);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    if(reverseDirection){
      reverseDirection = false;
    }
    else{
      reverseDirection = true;
    }
    Serial.println("inside a1");
    delay(1000);
  }
  Particle.process();
}