/*
  Arrays
 
 Demonstrates the use of  an array to hold pin numbers
 in order to iterate over the pins in a sequence. 
 Lights multiple LEDs in sequence, then in reverse.
 
 Unlike the For Loop tutorial, where the pins have to be
 contiguous, here the pins can be in any random order.
 
 The circuit:
 * LEDs from pins 2 through 7 to ground
 
 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Array
 */
int timer = 50;           // The higher the number, the slower the timing.
int ledPins[] = { 
 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };       // an array of pin numbers to which LEDs are attached
int pinCount = 12;           // the number of pins (i.e. the length of the array)

void setup() {
  int thisPin;
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }
}

void blinkAll(int numBlinks) {
  // for each blink
  for (int i = 0; i < numBlinks; i++) {
    // turn all LEDs on
    for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
      digitalWrite(ledPins[thisPin], HIGH);
    }
    delay(300);
    // turn all LEDs off
    for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
      digitalWrite(ledPins[thisPin], LOW);
    }
    delay(300);
  }
}


void loop() {
  // loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);   
    delay(timer);                  
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);    

  }
}


