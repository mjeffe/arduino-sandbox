/*
controls a full h-bridge circuit to drive a dc motor
 */

int m1dir = 2;
int m1speed = 3;
int pause = 2000;


// the setup routine runs once when you press reset:
/* ------------------------------------------------------- */
void setup() {
  pinMode(m1dir, OUTPUT);     
  pinMode(m1speed, OUTPUT);
  Serial.begin(9600);
}

void forward(int spd) {
  Serial.println("forward");
  digitalWrite(m1dir, HIGH);
  Serial.print("F speed ");
  Serial.println(spd);
  analogWrite(m1speed, spd);
  delay(pause);
}

void reverse(int spd) {
}

/* -------------------------------------------------------
 * MAIN
 * -------------------------------------------------------*/
void loop() {
  // forward
  Serial.println("forward");
  digitalWrite(m1dir, HIGH);
  Serial.println("F speed 75");
  analogWrite(m1speed, 75);
  delay(pause);
  Serial.println("F speed 175");
  analogWrite(m1speed, 175);
  delay(pause);
  Serial.println("F speed 225");
  analogWrite(m1speed, 225);
  delay(pause);

  // coast
  Serial.println("coast speed 0");
  analogWrite(m1speed, 0);
  delay(pause);

  // reverse
  Serial.println("reverse");
  digitalWrite(m1dir, LOW);
  Serial.println("R speed 75");
  analogWrite(m1speed, 75);
  delay(pause);
  Serial.println("R speed 175");
  analogWrite(m1speed, 175);
  delay(pause);
  Serial.println("R speed 225");
  analogWrite(m1speed, 225);
  delay(pause);

  // coast
  Serial.println("coast speed 0");
  analogWrite(m1speed, 0);
  delay(pause);
}



