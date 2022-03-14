/*
 * This is an extension of Martin2250's ADC touch examples
 * to have the library built in, for rapid deployment in workshop settings
 * 
 * this will send the output response to pin 11 (because it is the right spacing for a piezo buzzer to reach the gnd pin!)
 */

#include "ADCTouch.h"

int ref0, ref1;     //reference values to remove offset

int analogPinOut=11;
int val0constrained=0;

int val0high=120;
int val0low=0;

int threshold=40;



void setup() 
{
    // No pins to setup, pins can still be used regularly, although it will affect readings

    Serial.begin(9600);


    ref0 = ADCTouch.read(A0, 500);    //create reference values to 
    ref1 = ADCTouch.read(A1, 500);    //account for the capacitance of the pad

    pinMode(analogpinout,OUTPUT);
    digitalWrite(analogPinOut,HIGH);
} 

void loop() 
{
    int value0 = ADCTouch.read(A0);   //no second parameter
    int value1 = ADCTouch.read(A1);   //   --> 100 samples

    value0 -= ref0;       //remove offset
    value1 -= ref1;

    //Serial.print(value0 > threshold);    //send (boolean) pressed or not pressed
   // Serial.print("\t");           //use if(value > threshold) to get the state of a button

   // Serial.print(value1 > threshold);
   // Serial.print("\t\t");

    Serial.println(value0);             //send actual reading
    //Serial.print("\t");
  
    //Serial.println(value1);
    delay(5);

val0constrained = map(value0,val0low,val0high,0,255); // map from 0 to 255 for output for an LED or Buzzer
   
val0constrained = constrain(val0constrained,0,255); // extra make sure it doesn't go past

//    Serial.print("\t val0constrained = ");
  
  //  Serial.println(val0constrained);

    analogWrite(analogPinOut, val0constrained);

    
}
