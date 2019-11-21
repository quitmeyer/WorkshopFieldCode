/*
   This is an extension of Martin2250's ADC touch examples
   to have the library built in, for rapid deployment in workshop settings

   In this one, you can hook a servo directly up 
  and if the sensor passes a threshold, the servo will wiggle around

*/

#include "ADCTouch.h"

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int ref0, ref1;     //reference values to remove offset


int val0constrained = 0;

int val0high = 120;
int val0low = 0;

int threshold=40;


void setup()
{
  // No pins to setup, pins can still be used regularly, although it will affect readings

  Serial.begin(9600);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  ref0 = ADCTouch.read(A0, 500);    //create reference values to
  ref1 = ADCTouch.read(A1, 500);    //account for the capacitance of the pad
}

void loop()
{
  int value0 = ADCTouch.read(A0);   //no second parameter
  int value1 = ADCTouch.read(A1);   //   --> 100 samples

  value0 -= ref0;       //remove offset
  value1 -= ref1;

  Serial.print(value0 > threshold);    //send (boolean) pressed or not pressed
  Serial.print("\t");           //use if(value > threshold) to get the state of a button

  Serial.print(value1 > threshold);
  Serial.print("\t\t");

  Serial.print(value0);             //send actual reading
  Serial.print("\t");

  Serial.print(value1);
  delay(100);

if(value0>threshold){

 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}


}
