// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

char dbgbuf[80];

/****************************************************************************
 ***************************************************************************/
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

/****************************************************************************
 ***************************************************************************/
void ramp_up_ramp_down(AF_DCMotor motor) {
  int i, incr = 1, runtime = 1000;
  
  
  Serial.println("forward");
  
  motor.run(FORWARD);
  for (i=0; i < 255; i += incr) {
    //sprintf(dbgbuf, "i=%d,", i); Serial.print(dbgbuf);
    motor.setSpeed(i);  
    delay(10);
  }
  Serial.println("full speed");
  delay(runtime);
  Serial.println("ramping down");
  for (i=255; i > 0; i -= incr) {
    //sprintf(dbgbuf, "i=%d,", i); Serial.print(dbgbuf);
    motor.setSpeed(i);  
    delay(10);
  }
  motor.setSpeed(0);
  motor.run(RELEASE);
  delay(1000);
  
  Serial.println("backward");

  motor.run(BACKWARD);
  for (i=0; i < 255; i += incr) {
    //sprintf(dbgbuf, "i=%d,", i); Serial.print(dbgbuf);
    motor.setSpeed(i);  
    delay(10);
  }
  Serial.println("full speed");
  delay(runtime);
  Serial.println("ramping down");
  for (i=255; i > 0; i -= incr) {
    //sprintf(dbgbuf, "i=%d,", i); Serial.print(dbgbuf);
    motor.setSpeed(i);  
    delay(10);
  }
  motor.setSpeed(0);
  motor.run(RELEASE);

  Serial.println(" ");
  Serial.println("stoped");
}
 

/****************************************************************************
 ***************************************************************************/
void do_d(int n) {
   sprintf(dbgbuf, "do_d n=%d,", n); Serial.print(dbgbuf);
}

/****************************************************************************
 ***************************************************************************/
void do_s(int n) {
   sprintf(dbgbuf, "do_d n=%d,", n); Serial.print(dbgbuf);
}


/****************************************************************************
 * stuff for reading input from serial port (serial over USB)
 ***************************************************************************/
void check_inputs() {
   int len = 0, i = 0;
   char str[9];
   char num[9];
   int strsize = 9;
   char inchr = -1;

   str[0] = '\0';

   /* read the input */
   while (Serial.available() > 0) {
      if ( i < strsize - 1 ) {
         inchr = Serial.read();
         str[i++] = inchr;
         str[i] = '\0';
      }
      else {
         Serial.println("Error: too much input!");
         return;
      }
      //Serial.print("I received: "); Serial.println(str);
   }

   /* did we read anything? */
   len = strlen(str);
   if ( len == 0 ) {
      return;
   }

   /* adjust parameters */
   i = 0;
   /* motor number */
   if ( str[0] == 'm' ) {

      if ( str[2] == 'd' ) {
         strncpy(num, str+1, len-1);
         do_t(atoi(num));
      }
   }
   else if ( str[0] == 's' ) {
      strncpy(num, str+1, len-1);
      do_s(atoi(num));
   }
   else {
      Serial.print("Error: unknown parameter '"); Serial.print(str); Serial.println("'");
      return;
   }
}


/****************************************************************************
 ***************************************************************************/
void loop() {
  ramp_up_ramp_down(m1);
  ramp_up_ramp_down(m2);
  //ramp_up_ramp_down(m3);
  //ramp_up_ramp_down(m4);

 
  delay(1000);  
}
