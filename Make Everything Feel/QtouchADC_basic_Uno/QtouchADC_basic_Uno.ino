#include <ADCTouch.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int ref0, ref1;       //reference values to remove offset
int val; 
int valmax=-1000;
int valmin=1000;

void setup() 
{
    // No pins to setup, pins can still be used regularly, although it will affect readings

    Serial.begin(9600);

    ref0 = ADCTouch.read(A0, 100);    //create reference values to 
    ref1 = ADCTouch.read(A1, 100);      //account for the capacitance of the pad

      myservo.attach(11);  // attaches the servo on pin 9 to the servo object

} 

void loop() 
{
    int value0 = ADCTouch.read(A0);   //no second parameter
    int value1 = ADCTouch.read(A1);     //   --> 100 samples

    value0 -= ref0;       //remove offset
    value1 -= ref1;

    Serial.print("A0 \t");

    Serial.print(value0 > 40);    //return pressed or not pressed
    Serial.print("  A0 raw \t");
        Serial.print(value0);             //return value
            Serial.print("\t");
    Serial.print("\t");

    Serial.print(value1 > 40);
    Serial.print(" A1 \t\t");

    Serial.print("\t");
    Serial.println(value1);

      val = value0;            // reads the value of the potentiometer (value between 0 and 1023)

if(val>valmax) valmax=val;
if(val<valmin) valmin=val;

        Serial.print("\t Val min and Max:  ");
    Serial.println(valmin);
        Serial.println(valmax);

   

  val = map(val, valmin, valmax, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value

 delay(100);
}

