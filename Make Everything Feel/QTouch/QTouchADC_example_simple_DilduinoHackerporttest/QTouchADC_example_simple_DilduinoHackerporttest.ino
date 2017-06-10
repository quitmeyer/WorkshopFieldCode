#include <QTouchADCduino.h>

int refPin  = A2;

int ref1 = 0;

int sensorpin = A3;

void setup() {

    Serial.begin(9600);
  QTouchADCduino.init();
 // ref1 = QTouchADCduino.sense(sensorpin, refPin, 64);
  
}

void loop() {

  int value1 = (QTouchADCduino.sense(sensorpin, refPin, 16) - ref1);

  Serial.println(value1);

  delay(100);
}
