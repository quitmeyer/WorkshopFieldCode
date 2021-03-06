// qTouchADC based on urban's code....

/*
   For Feeling Plants,
   Connect the sense pin (pb4) to a target plant (an herbaceous (green) part of the plant) .

   It should be able to pick up your hand near or grabbing the plant. Try it out with many different kinds.

   If your device is grounded already to something like your laptop, you don't need to connect the GND to a different plant
    If you are in the wild or on battery power - connect the ground to an herbaceous (green) part of a plant growing in the ground

*/



int refPin  = PB2;
int sensePin2 =  PB4;
int ledPin2 = PB1;
int speakerPin = PB0;
int lowthresh = 4;
//SoftwareSerial mySerial(5, 5); // RX, TX

int value1 = 0;
int ref1 = 0;
int value2 = 0;
int ref2 = 0;
int QTouchDelay = 5;
int measurement1, measurement2;

void initADC() {
  // ADC
  ADMUX = (0 << REFS0); //REFS0=0:VCC reference, =1:internal reference 1.1V
  ADCSRA = (1 << ADEN) | (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //ADC enable, prescaler 8
  //ADCSRA = (1<<ADEN)| (1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0); //ADC enable, prescaler 16
  //ADCSRA = (1<<ADEN)| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC enable, prescaler 128
}

// pre: adcPin == beliebiger ADC pin, ausser A0. A0 (ADC0/PC0) wird als Referenz gebraucht.
uint16_t sensePad(uint8_t adcPin, uint8_t refPin, uint8_t samples) {
  long _value = 0;
  int muxAdc = 0;
  int muxRef = 0;

  if (adcPin == PB3) muxAdc = 0x03;
  if (adcPin == PB4) muxAdc = 0x02;
  if (adcPin == PB2) muxAdc = 0x01;
  if (adcPin == PB5) muxAdc = 0x00;

  if (refPin == PB3) muxRef = 0x03;
  if (refPin == PB4) muxRef = 0x02;
  if (refPin == PB2) muxRef = 0x01;
  if (refPin == PB5) muxRef = 0x00;

  for (int _counter = 0; _counter < samples; _counter ++)
  {
    // first measurement: adcPin low, S/H high
    ADMUX = (0 << REFS0) | (muxRef); // set ADC sample+hold condenser to the free A0 (ADC0)
    //delayMicroseconds(QTouchDelay);
    PORTB |= (1 << refPin); //PC0/ADC0 ref/ S/H high (pullup or output, doesn't matter)
    PORTB &= ~(1 << adcPin);
    DDRB |= (1 << adcPin) | (1 << refPin); // both output: adcPin low, S/H (ADC0) high
    delayMicroseconds(QTouchDelay);
    DDRB &= ~((1 << adcPin) | (1 << refPin)); // set pins to Input...
    PORTB &= ~((1 << adcPin) | (1 << refPin)); // ... and low: Tristate

    ADMUX = (0 << REFS0) | (muxAdc); //  read extern condensator from adcPin
    ADCSRA |= (1 << ADSC); // start conversion
    while (!(ADCSRA & (1 << ADIF))); // wait for conversion complete
    ADCSRA |= (1 << ADIF); // clear ADIF
    measurement1 = ADC;

    //measurement1 = analogRead(adcPin);

    // second measurement: adcPin high, S/H low
    ADMUX = (0 << REFS0) | (muxRef); // set ADC sample+hold condenser to the free PC0 (ADC0)
    //delayMicroseconds(QTouchDelay);
    PORTB |= (1 << adcPin); // sensePad/adcPin high
    //PORTB &= ~(1<<refPin);
    DDRB |= (1 << adcPin) | (1 << refPin); // both output: adcPin high, S/H (ADC0) low
    delayMicroseconds(QTouchDelay);
    DDRB &= ~((1 << adcPin) | (1 << refPin));
    PORTB &= ~((1 << adcPin) | (1 << refPin));

    ADMUX = (0 << REFS0) | (muxAdc); //   read extern condensator from adcPin
    ADCSRA |= (1 << ADSC); // start conversion
    while (!(ADCSRA & (1 << ADIF))); // wait for conversion complete
    ADCSRA |= (1 << ADIF); // clear ADCIF
    measurement2 = ADC;

    //measurement2 = analogRead(adcPin);

    _value += (measurement2 - measurement1);

  }

  return _value / samples;
}

void setup() {

  TCCR0B = TCCR0B & 0b11111011; //timer pre-scaler divided by 8, slower speed of the processor
  pinMode(speakerPin, OUTPUT);

  //mySerial.begin(38400);
  //mySerial.println("Hello, world?");

  // TCCR0B = TCCR0B & 0b11111001; //timer pre-scaler divided by 1

  pinMode(ledPin2, OUTPUT);
  delay(200);

  initADC();

  delay(200);

  ref2 = sensePad(sensePin2, refPin, 500);

}

void loop() {

  unsigned long time = 0;

  time = micros() - time;

  value2 = (sensePad(sensePin2, refPin, 100) - ref2);


  value2 = (value2 - lowthresh) * 4;

  if (value2 <= 0) value2 = 0;
  if (value2 >= 255) value2 = 255;

  analogWrite(ledPin2, value2);
  // analogWrite(speakerPin, value2);
 if(value2>10){
  beep(speakerPin, 8000 - value2 * 40, 10);
//beepvol(speakerPin, 2093 + value2 * 10, 10,100);
 }
  delay(1);
}


void scale (char note)
{
  if (note == 'C')
    beep(speakerPin, 2093, 500); //C: play the note C (C7 from the chart linked to above) for 500ms
  if (note == 'D')
    beep(speakerPin, 2349, 500); //D
  if (note == 'E')
    beep(speakerPin, 2637, 500); //E
  if (note == 'F')
    beep(speakerPin, 2793, 500); //F
  if (note == 'G')
    beep(speakerPin, 3136, 500); //G
  if (note == 'A')
    beep(speakerPin, 3520, 500); //A
  if (note == 'B')
    beep(speakerPin, 3951, 500); //B
  if (note == 'H')
    beep(speakerPin, 4186, 500); //C
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) // the sound producing function
{
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
    //break;
  }

}

void beepvol (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds, int vol) // the sound producing function
{
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++) {
    analogWrite(speakerPin, vol);
    delayMicroseconds(delayAmount);
    analogWrite(speakerPin, vol);
    delayMicroseconds(delayAmount);
    //break;
  }

}
