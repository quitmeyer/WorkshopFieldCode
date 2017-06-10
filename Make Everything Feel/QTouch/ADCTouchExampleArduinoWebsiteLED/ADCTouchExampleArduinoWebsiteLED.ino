#include <ADCTouch.h>

int ref0, ref1;       //reference values to remove offset
int led = 13;

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 9999;        // minimum sensor value
int sensorMax = -9999;           // maximum sensor value

void setup() 
{
    // No pins to setup, pins can still be used regularly, although it will affect readings

    Serial.begin(9600);
pinMode(led, OUTPUT);
    ref0 = ADCTouch.read(A2, 500);    //create reference values to 
    ref1 = ADCTouch.read(A3, 500);      //account for the capacitance of the pad


 // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
   digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
    delay(100);
     digitalWrite(13, LOW);
  delay(100);
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);

  // calibrate during the first four seconds 
  while (millis() < 4000) {
         sensorValue = ADCTouch.read(A2);   
         sensorValue -= ref0;


    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
    delay(100);
     digitalWrite(13, LOW);
  delay(100);
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);

} 

void loop() 
{
    int value0 = ADCTouch.read(A2);   //no second parameter
    int value1 = ADCTouch.read(A3);     //   --> 100 samples

    value0 -= ref0;       //remove offset
    value1 -= ref1;

    Serial.print(value0 > 40);    //return pressed or not pressed
    Serial.print("\t");
    Serial.print(value1 > 40);
    Serial.print("\t\t");
     value0=constrain(map(value0,sensorMin,sensorMax,0,255),0,255);
    Serial.print(value0);             //return value
    Serial.print("\t");
    Serial.println(value1);
    
    
    analogWrite(led,value0
   );
   
   
    delay(100);
}
