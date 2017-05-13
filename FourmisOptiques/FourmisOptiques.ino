/*
Basic code we used in Madagascar to calibrate and make sound and flash leds when insects dtected on fiber optics
Part of hte Hacking the Wild Project

*/

int sensorPin= 1;//analog pin ref!!!
int diffPin=1;
int threshPin=0;
int spDiff=4;
int spThresh=3;

int thresh=10;

int bglight=0;

int newreading=0;
int diffreading=0;

void setup(){
  //pinMode(sensorPin, INPUT_PULLUP); // NOTE THERE"S SOMETHING ELSE FOR ATTINIES
  pinMode(2,INPUT); //SensorPin  // have to refer to the digital pin you have to call it 2
  //digitalWrite(2, HIGH); // make sure yeah!

  pinMode(spDiff,OUTPUT);
  pinMode(spThresh,OUTPUT);

  pinMode(diffPin,OUTPUT);
  pinMode(threshPin,OUTPUT);
  digitalWrite(diffPin,LOW);
  digitalWrite(threshPin,LOW);

  //get away for 2 seconds
  delay(2000);

  //calibrate

  long counter=0;
  long readingtotal=0;
  long thetime=millis();

  //BEEP ONCE
  myBeep(spThresh,500);
  digitalWrite(threshPin,HIGH);
  delay(200);
  digitalWrite(threshPin,LOW);
  
  while(millis()-thetime<1000){
    newreading=analogRead(sensorPin);
    counter++;
    readingtotal= readingtotal +newreading;
  }
  
  bglight = readingtotal/counter;

  //BEEP TWice
  myBeep(spThresh,10000);

  digitalWrite(threshPin,HIGH);
  delay (100);
  digitalWrite(threshPin,LOW);
  delay(100);
  digitalWrite(threshPin,HIGH);
  delay (100);
  digitalWrite(threshPin,LOW);

}



void loop(){
  //Get the reading  
  newreading=analogRead(sensorPin);
  //See if it is different than background calibration;
  diffreading= abs(newreading-bglight);

  //output this difference

  analogWrite(diffPin,map(diffreading,0,1023,0,255));
  myBeep(spDiff,map(diffreading,0,1023,500,10000));

  //output a threshold
  if(diffreading>thresh){
    analogWrite(threshPin,diffreading);
    myBeep(spThresh,map(diffreading,0,1023,500,10000));
  }





}


void myBeep (unsigned char speaker, int frequencyInHertz)     // the sound producing function
{ 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);

  digitalWrite(speaker,HIGH);
  delayMicroseconds(delayAmount);
  digitalWrite(speaker,LOW);
  delayMicroseconds(delayAmount);

} 






