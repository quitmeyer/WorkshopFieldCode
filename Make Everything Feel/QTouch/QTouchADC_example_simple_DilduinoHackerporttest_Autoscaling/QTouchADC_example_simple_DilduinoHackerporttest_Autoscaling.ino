#include <QTouchADCduino.h>

int refPin  = A9;

int ref1 = 0;

int sensorpin = A7;

int sensorMin = 9999;        // minimum sensor value
int sensorMax = -9999;           // maximum sensor value

void setup() {

    Serial.begin(9600);
  QTouchADCduino.init();
 // ref1 = QTouchADCduino.sense(sensorpin, refPin, 64);
 pinMode(13,OUTPUT);
  
}

void loop() {

  int value1 = (QTouchADCduino.sense(sensorpin, refPin, 16) - ref1);
  
      // record the maximum sensor value
    if (value1 > sensorMax) {
      sensorMax = value1;
    }

    // record the minimum sensor value
    if (value1 < sensorMin) {
      sensorMin = value1;
    }

  Serial.println(value1);
  
  analogWrite(13, constrain(map(value1,sensorMin,sensorMax,0,255),0,255));

  delay(100);
}
