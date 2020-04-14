// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

// --------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Robot Arm");

  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

// --------------------------------------------------------------------------
void motor_go(AF_DCMotor m, int direction, uint8_t top_speed) {
   int i, max_speed = 255, incr ;
  
   m.run(direction);
   for (i = 0; i < top_speed; i++) {
      m.setSpeed(i);  
      delay(10);
   }
}

// --------------------------------------------------------------------------
void motor_stop(AF_DCMotor m, uint8_t top_speed) {
   uint8_t i;

   for (i = top_speed; i != 0; i--) {
      m.setSpeed(i);  
      delay(10);
   }
   m.run(RELEASE);
}


// --------------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------------
void loop() {
   Serial.println("m1 forward");  
   motor_go(m1, FORWARD, 100);
   delay(200);
   Serial.println("m1 stop");
   motor_stop(m1, 100);
   delay(1000);
   
   Serial.println("m1 backward");
   motor_go(m1, BACKWARD, 100);
   delay(30);
   Serial.println("m1 stop");
   motor_stop(m1, 100);
   delay(1000);

/*
   Serial.println("m2 forward");
   motor_go(m2, FORWARD, 100);
   delay(30);
   Serial.println("m2 stop");
   motor_stop(m2, 100);
   Serial.println("m2 backward");
   motor_go(m2, BACKWARD, 100);
   delay(30);
   Serial.println("m2 stop");
   motor_stop(m2, 100);
*/

}



