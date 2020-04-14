/*
controls a full h-bridge circuit to drive a dc motor
 */

int r1 = 13;
int r2 = 12;
int r3 = 11;
int r4 = 10;
int pause = 2000;


// the setup routine runs once when you press reset:
/* ------------------------------------------------------- */
void setup() {
  pinMode(r1, OUTPUT);     
  pinMode(r2, OUTPUT);     
  pinMode(r3, OUTPUT);     
  pinMode(r4, OUTPUT);     
}

/* ------------------------------------------------------- */
void forward() {
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
}

/* ------------------------------------------------------- */
void reverse() {
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);
}

/* ------------------------------------------------------- */
void breaks() {
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
}

/* ------------------------------------------------------- */
void coast() {
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  digitalWrite(r4, HIGH);
}

/* -------------------------------------------------------
 * MAIN
 * -------------------------------------------------------*/
void loop() {
  forward();
  delay(pause);
  coast();
  delay(pause);
  reverse();
  delay(pause);
  coast();
  delay(pause);
}



