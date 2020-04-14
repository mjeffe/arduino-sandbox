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
  Serial.println("F on");
  digitalWrite(m1speed, HIGH);
  delay(pause);
  Serial.println("F off");
  digitalWrite(m1speed, LOW);
  delay(pause);
  Serial.println("F on");
  digitalWrite(m1speed, HIGH);
  delay(pause);
  Serial.println("F off");
  digitalWrite(m1speed, LOW);
  delay(pause);


  Serial.println("reverse");
  digitalWrite(m1dir, LOW);
  Serial.println("R on");
  digitalWrite(m1speed, HIGH);
  delay(pause);
  Serial.println("R off");
  digitalWrite(m1speed, LOW);
  delay(pause);
  Serial.println("R on");
  digitalWrite(m1speed, HIGH);
  delay(pause);
  Serial.println("R off");
  digitalWrite(m1speed, LOW);
  delay(pause);
}



