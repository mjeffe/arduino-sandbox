/****************************************************************************
 * $Id: metronome.ino 292 2016-06-18 01:26:23Z u35616872 $
 *
 * Metronome
 *
 * Connect a peizo buzzer's + to pin 9 and - to gnd
 * Open the arduino's tools->serial monitor. At startup this will output
 * instructions on how to change the tempo and signature,
 ***************************************************************************/
int speaker_pin = 9;
int led_pin = 13;

/*
 * char notenames[] = { 'c',  'd',  'e',  'f',  'g',  'a',  'b',  'C' };
 * int      tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 */

/* times set in milliseconds */
int beat_tone = 100;
int accent_tone = 300;
int tone_duration = 20;
int delay_duration = 0;

/* input variables - set defaults here */
int beats_per_minute = 60;    // tempo
int beats_per_measure = 4;    // time signature


/* --------------------------------------------------------------------------
 * ------------------------------------------------------------------------*/
void calc_delay() {
   /* delay_duration is what sets the tempo. Adjust here to milliseconds and
    * subtract the amount of time it takes to play the tone */
   delay_duration = (60 / (float)beats_per_minute * 1000) - tone_duration;
   /* add a few ms to account for arduino doing other stuff */
   delay_duration += 20;
   // Serial.print("delay_duration: "); Serial.println(delay_duration);
 
}

/* --------------------------------------------------------------------------
 * stuff for reading input from serial port (serial over USB)
 * ------------------------------------------------------------------------*/
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

   /* adjust parameter */
   i = 0;
   if ( str[i] == 't' ) {
      strncpy(num, str+1, len-1);
      beats_per_minute = atoi(num);
      Serial.print(  "tempo = "); Serial.print(beats_per_minute); Serial.println(" beats per minute");
      /* recalculate the delay since tempo has changed */
      calc_delay();

   }
   else if ( str[i] == 's' ) {
      strncpy(num, str+1, len-1);
      beats_per_measure = atoi(num);
      Serial.print(  "time signature = "); Serial.print(beats_per_measure); Serial.println(" beats per measure");
   }
   else {
      Serial.print("Error: unknown parameter '"); Serial.print(str); Serial.println("'");
      return;
   }
}


/* --------------------------------------------------------------------------
 * ------------------------------------------------------------------------*/
void setup() {
   Serial.begin(9600);

   // set i/o pins
   pinMode(speaker_pin, OUTPUT);
   pinMode(led_pin, OUTPUT);

   calc_delay();

   /* print instructions on how to adjust tempo and time signature */
   Serial.println("=============== Starting ===============");
   Serial.print(  "tempo = "); Serial.print(beats_per_minute); Serial.println(" beats per minute");
   Serial.print(  "time signature = "); Serial.print(beats_per_measure); Serial.println(" beats per measure");
   Serial.println(" ");
   Serial.println("To adjust tempo type tNN where NN is the new tempo");
   Serial.println("To adjust signature type sN where N is the new number of beats in a masure");
   Serial.println("========================================");
}

/* --------------------------------------------------------------------------
 * ------------------------------------------------------------------------*/
void loop() {
   int i = 0;

   digitalWrite(led_pin, HIGH);
   tone(speaker_pin, accent_tone, tone_duration);
   digitalWrite(led_pin, LOW);
   delay(delay_duration);
   for ( i = 0; i < beats_per_measure - 1; i++ ) {
      digitalWrite(led_pin, HIGH);
      tone(speaker_pin, beat_tone, tone_duration);
      digitalWrite(led_pin, LOW);
      delay(delay_duration);
   }

   check_inputs();
}


