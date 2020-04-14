// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

char dbgbuf[20];

uint8_t      num_motors = 4;
AF_DCMotor   motors[4] = {1,2,3,4};
uint8_t      speeds[4] = {0,0,0,0};
uint8_t      directions[4] = {RELEASE,RELEASE,RELEASE,RELEASE};


// ----------------------------------------------------------------- 
void setup() {
   uint8_t = i;
   Serial.begin(9600);
   Serial.println("Motor test!");

   for ( i=0; i < num_motors; i++ ) {
      motor[i].run(RELEASE);
   }
}

// ----------------------------------------------------------------- 
void run_motors() {
   uint8_t i;

   for ( i=0; i < num_motors; i++ ) {
      motor[i].run(directions[i]);
      motor[i].setSpeed(speeds[i]);  
   }
}

// ----------------------------------------------------------------- 
void set_motor(uint8_t motor, uint8_t dir, uint8_t speed) {
   uint8_t i;

   directions[motor] = dir;
   speeds[motor] = speed;  
}

// ----------------------------------------------------------------- 
void ramp_up_ramp_down(AF_DCMotor motor) {
  int i, incr = 8, runtime = 100;
  
  motor.run(FORWARD);
  for (i=0; i < 255; i += incr) {
    motor.setSpeed(i);  
    delay(10);
  }
  delay(runtime);
  for (i=255; i > 0; i -= incr) {
    motor.setSpeed(i);  
    delay(10);
  }
  motor.setSpeed(0);
  motor.run(RELEASE);
  delay(500);
  
  motor.run(BACKWARD);
  for (i=0; i < 255; i += incr) {
    motor.setSpeed(i);  
    delay(10);
  }
  delay(runtime);
  for (i=255; i > 0; i -= incr) {
    motor.setSpeed(i);  
    delay(10);
  }
  motor.setSpeed(0);
  motor.run(RELEASE);
}
 

// ----------------------------------------------------------------- 
void loop() {
   ramp_up_ramp_down(m1);
   ramp_up_ramp_down(m2);

   //set_motor(1,FORWARD,100);
 
   delay(1000);  
}
