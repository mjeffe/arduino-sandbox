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
int dAmount = 10;
int timer = 5;           // The higher the number, the slower the timing.
int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };       // an array of pin numbers to which LEDs are attached
int pinCount = 12;           // the number of pins (i.e. the length of the array)

// ----------------------------------------------------------
void setup() {
  int thisPin;
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }
}

// ----------------------------------------------------------
void blinkAll(int blinks) {
  // for each blink
  for (int i = 0; i < blinks; i++) {
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

/* -------------------------------------------------------
 * blinks all LEDs from left to right using rate milliseconds
 * between each LET on/off
 */
void dLeftToRight(int rate) {
  
  // loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);   
    delay(rate);                  
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);    

  }
}
  
/* -------------------------------------------------------
 * blinks all LEDs from right to left using rate milliseconds
 * between each LET on/off
 */
void dRightToLeft(int rate) {
  // loop from the highest pin to the lowest:
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);
    delay(rate);
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);
  }
}

/* -------------------------------------------------------
 * blinks all LEDs back and forth one time, using rate milliseconds
 * between each LET on/off
 */
void sideToSide(int rate) {
  dLeftToRight(rate);  
  dRightToLeft(rate);
}

// -------------------- main ---------------------------------
void slow_to_fast() {
  //sideToSide(timer);  
  
  if ( dAmount > 0 ) {
    dLeftToRight(timer);
  } else {
    dRightToLeft(timer);
  }

  timer = timer + dAmount;
  if (timer <= 5 || timer >= 100) {
    dAmount = -dAmount ; 
    blinkAll(4);
  }

  if ( dAmount > 0 ) {
    dLeftToRight(timer);
  } else {
    dRightToLeft(timer);
  }

}

// -------------------- main ---------------------------------
void loop() {
  slow_to_fast();
  //sideToSide(40);
}



