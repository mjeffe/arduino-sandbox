/****************************************************************************
 * $Id: piezo2.ino 193 2014-03-04 23:56:36Z u35616872 $
 *
 * Metronome
 *
 ***************************************************************************/
int speaker_pin = 9;

char notenames[] = { 'c',  'd',  'e',  'f',  'g',  'a',  'b',  'C' };
int      tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

int beat_tone = 200;
int accent_tone = 300;
int tempo = 300;  //90;             // beats per minute
int beats_per_measure = 4;  // time signature


void setup() {
   pinMode(speaker_pin, OUTPUT);
}

void loop() {
   int i = 0;

   //play_tone(accent_tone, tempo);
   tone(speaker_pin, accent_tone, tempo / 2);
   delay(tempo * 2);
   for ( i = 0; i < beats_per_measure - 1; i++ ) {
      //play_tone(beat_tone, tempo);
      tone(speaker_pin, beat_tone, tempo / 2);
      delay(tempo * 2);
   }
}


