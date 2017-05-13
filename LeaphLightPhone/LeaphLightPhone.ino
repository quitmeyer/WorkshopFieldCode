void setup(){
  pinMode(2,INPUT); 
  digitalWrite(2, HIGH); 
  pinMode(3, OUTPUT);
}

void loop(){
  myBeep(3,map(analogRead(1),0,1023,500,10000));
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








