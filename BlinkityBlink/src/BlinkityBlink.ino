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
void decToBin(unsigned n) 
{ 
	int a[3], i;    

  for(i=0; n>0; i++){    
    a[i]=n%2;    
    n= n/2; 
  } 

  x = a[2];
  y = a[1];
  z = a[0];

  printf("%d,%d,%d",x,y,z);
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led0,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(switchy0,INPUT_PULLUP);
  pinMode(switchy1,INPUT_PULLUP);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(digitalRead(switchy0) == LOW && initalValue < 8){
    decToBin(initalValue);
    // x==1 ? digitalWrite(led0,HIGH): digitalWrite(led0,LOW);
    // y==1 ? digitalWrite(led1,HIGH): digitalWrite(led1,LOW);
    // z==1 ? digitalWrite(led2,HIGH): digitalWrite(led2,LOW);
    initalValue += 1;
  }
  else if(digitalRead(switchy1) == LOW){
    digitalWrite(D0,LOW);
    digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
  }
  
}