#include <AFMotor.h>


AF_Stepper motor(48, 2);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  motor.setSpeed(10);  // 10 rpm   

  motor.step(100, FORWARD, SINGLE); 
  motor.release();
  delay(1000);
}

void loop() {
  Serial.println("forward single");
  motor.step(100, FORWARD, SINGLE); 
  Serial.println("backward single");
  motor.step(100, BACKWARD, SINGLE); 

  Serial.println("forward double");
  motor.step(100, FORWARD, DOUBLE); 
  Serial.println("backward double");
  motor.step(100, BACKWARD, DOUBLE);

  Serial.println("forward interleave");
  motor.step(100, FORWARD, INTERLEAVE); 
  Serial.println("backward interleave");
  motor.step(100, BACKWARD, INTERLEAVE); 

  Serial.println("forward microstep");
  motor.step(100, FORWARD, MICROSTEP); 
  Serial.println("backward microstep");
  motor.step(100, BACKWARD, MICROSTEP); 
}
