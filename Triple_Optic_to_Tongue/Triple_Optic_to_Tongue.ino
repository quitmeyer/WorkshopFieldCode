/*
Simple Code for the Fiber Optic Jungle Insect Traffic Taster

Senses insects on fiber optic strips hung around the jungle
sends electric shocks to a tongue display made from a leaf

public domain

*/

int sensorPin= A3;//analog pin ref!!!
int diffPin=9;

int sensorPin1= A1;//analog pin ref!!!
int diffPin1=10;


int sensorPin2= A2;//analog pin ref!!!
int diffPin2=11;





int thresh=100;

int bglight=0;
int bglight1=0;
int bglight2=0;

int newreading=0;
int diffreading=0;

int newreading1=0;
int diffreading1=0;

int newreading2=0;
int diffreading2=0;

void setup(){
Serial.begin(9600);
  pinMode(sensorPin,INPUT_PULLUP);
    pinMode(sensorPin1,INPUT_PULLUP);
  pinMode(sensorPin2,INPUT_PULLUP);



  pinMode(diffPin,OUTPUT);
  pinMode(diffPin1,OUTPUT);
    pinMode(diffPin2,OUTPUT);

  digitalWrite(diffPin,LOW);
    digitalWrite(diffPin1,LOW);
      digitalWrite(diffPin2,LOW);



  //get away for 2 seconds
  delay(2000);

  //calibrate
//**----------
  long counter=0;
  long readingtotal=0;
  long thetime=millis();

  //BEEP ONCE
    Serial.println("Start Calibrate");

  digitalWrite(diffPin,HIGH);
  delay(200);
  digitalWrite(diffPin,LOW);
  
  while(millis()-thetime<1000){
    newreading=analogRead(sensorPin);
    counter++;
    readingtotal= readingtotal +newreading;
  }
  
  bglight = readingtotal/counter;
//****/

//**----------
  counter=0;
  readingtotal=0;
  thetime=millis();
  
  while(millis()-thetime<1000){
    newreading1=analogRead(sensorPin1);
    counter++;
    readingtotal= readingtotal +newreading1;
  }
  
  bglight1 = readingtotal/counter;
//****/

//**----------
  counter=0;
  readingtotal=0;
  thetime=millis();


  while(millis()-thetime<1000){
    newreading2=analogRead(sensorPin2);
    counter++;
    readingtotal= readingtotal +newreading2;
  }
  
  bglight2 = readingtotal/counter;
//****/


  //BEEP TWice
  digitalWrite(diffPin,HIGH);
    digitalWrite(13,HIGH);

  delay (100);
  digitalWrite(diffPin,LOW);
      digitalWrite(13,LOW);

  delay(100);
  digitalWrite(diffPin,HIGH);
      digitalWrite(13,HIGH);

  delay (100);
  digitalWrite(diffPin,LOW);
    digitalWrite(13,LOW);

    Serial.println("End Calibrate");


}



void loop(){
  //Get the reading ****  
  newreading=analogRead(sensorPin);
  Serial.print("R0: ");
  Serial.print(newreading);
  //See if it is different than background calibration;
  diffreading= abs(newreading-bglight);

  //output this difference

  analogWrite(diffPin,map(diffreading,30,170,0,255));

  //output a threshold
  if(diffreading>thresh){
    //analogWrite(threshPin,diffreading);
  }



  //Get the reading ****  
  newreading1=analogRead(sensorPin1);
  Serial.print(" R1: ");
  Serial.print(newreading1);
  //See if it is different than background calibration;
  diffreading1= abs(newreading1-bglight1);

  //output this difference

  analogWrite(diffPin1,map(diffreading1,30,170,0,255));

  //output a threshold
  if(diffreading1>thresh){
    //analogWrite(threshPin,diffreading);
  }

  //Get the reading ****  
  newreading2=analogRead(sensorPin2);
  Serial.print(" R2: ");
  Serial.println(newreading2);
  //See if it is different than background calibration;
  diffreading2= abs(newreading2-bglight2);

  //output this difference

  analogWrite(diffPin2,map(diffreading2,30,170,0,255));

  //output a threshold
  if(diffreading2>thresh){
    //analogWrite(threshPin,diffreading);
  }







}








