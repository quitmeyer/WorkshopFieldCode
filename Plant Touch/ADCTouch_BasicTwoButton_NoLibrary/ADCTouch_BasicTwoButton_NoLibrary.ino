/*
 * This is an extension of Martin2250's ADC touch examples
 * to have the library built in, for rapid deployment in workshop settings
 * 
 */

#include "ADCTouch.h"

int ref0, ref1;     //reference values to remove offset
int threshold=40;


void setup() 
{
    // No pins to setup, pins can still be used regularly, although it will affect readings

    Serial.begin(9600);

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
  
    Serial.println(value1);
    delay(100);
}
