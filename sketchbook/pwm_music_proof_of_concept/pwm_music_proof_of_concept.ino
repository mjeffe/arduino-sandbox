/* experimental code to see what all I can do with LEDS on digital pins.  */
/* NOTE: attach a speaker via 100-ohm resister to pin 9 for a real treat. */

#define LEDSTARTPIN 2
#define LEDSTOPPIN 13 
#define NUMLIGHTS 12

void setup()
{
  int i;
  
  // start serial port at 9600 bps:
  Serial.begin(9600);
  for (i = LEDSTARTPIN; i <= LEDSTOPPIN; i++)
  {
    pinMode(i, OUTPUT);  
  }
}


void setLights(unsigned int lightBits)
{
   int i;

//#define OBVIOUS_CODE

#ifdef OBVIOUS_CODE  /* straight forward, but much slower. */
   for (i = 0; i < NUMLIGHTS; i++)
   {
      if (lightBits & 1 << i)      
        digitalWrite(LEDSTOPPIN - i, 1);
      else
        digitalWrite(LEDSTOPPIN - i, 0);
   }
#else   /* less obvious but functionally equivalent and f-a-s-t. */

//#define FLIP_LIGHTS

#ifdef FLIP_LIGHTS
    /* flip lightBits */ 
   lightBits = (lightBits         ) << 8 | (lightBits         ) >> 8; 
   lightBits = (lightBits & 0x0F0F) << 4 | (lightBits & 0xF0F0) >> 4;
   lightBits = (lightBits & 0x3333) << 2 | (lightBits & 0xCCCC) >> 2;
   lightBits = (lightBits & 0x5555) << 1 | (lightBits & 0xAAAA) >> 1;
   lightBits >>= 4;  // for 12 LEDS 
#endif // FLIP_LIGHTS

   /* lower 6 bits of PORTB are pins 13, 12, 11, 10, 9, 8 */ 
   PORTB = (PORTB & 0xC0) | (lightBits >> 6); 
   /* upper 6 bites of PORTD are pins 7, 6, 5, 4, 3, 2 */
   PORTD = (PORTD & 0x03) | ((lightBits << 2) & 0xFC); 

#endif  // NON OBVIOUS_CODE

}  


void attract_fadeout()
{ 

    int i, j, k; 
    unsigned int display;
   
  // loop a few times 
  for (k = 0; k < 4; k++)
  {  
    // fade in
    for (i = 0; i < 255; i++) 
    {
       for (j = 0; j < 255; j++)
       { 
           if (j > i)
             display = 0x0000;
           else 
             display = 0x0FFF; 
           setLights(display); 
       }
    }
    // fade out
    for (i = 0; i < 255; i++) 
    {
       for (j = 0; j < 255; j++)
       { 
           if (j > i)
             display = 0x0FFF;
           else 
             display = 0x0000; 
           setLights(display); 
       }
    }
  }
}

void pwmchase()
{ 
    /* bit-bang PWM */
    unsigned short disp; 
    int pwmvalues[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; /* 0 to 16 */ 
  for (int j = 0; j < 2; j++)
  {
    int x = 1;
    int xincr = 1; 
    while (x >= 1) 
    {  
         for (int c = 0; c < 16; c++)
         {  
             disp = 0; 
             for (int l = 0; l < 12; l++)      
                 if(pwmvalues[l] > c)
                     disp |= (1 << l);
             setLights(disp);
         }
              
         x += xincr; 
         if (x > (1024*11) || x < 1)
             xincr *= -1; 
         for (int l = 0; l < 12; l++)
         {
             pwmvalues[l] = abs(l * 1024 - x);      
             if (pwmvalues[l] > 1024) 
                 pwmvalues[l] = 1024; 
             pwmvalues[l] = 1024 - pwmvalues[l];
             pwmvalues[l] >>= 6;
         }
    }
  }
}    

 
void hardwarePWM() 
{ 
    unsigned char pwmstates[6] = {0,0,0,0,0,0}; 
    unsigned char pwmpins[6] = {3,5,6,9,10,11};
    
    int i, j;
    
    setLights(0);
    
  for (j = 20; j >= 0; j--)
    for (i = 0; i < 6; i++)
    { 
        unsigned char newstate =  j > 0 ? (random() % 3) * 127 : 0; 
        while (newstate != pwmstates[i])
        { 
            if (newstate > pwmstates[i])
              pwmstates[i]++;
            else
              pwmstates[i]--;
            analogWrite(pwmpins[i], pwmstates[i]);
            delay(1);
        }
    }
}
 
// The frequencies for piano notes can be derived from formula.
// I simply downloaded them from Professor Bryan Suits at Michigan Tech.
//http://www.phy.mtu.edu/~suits/notefreqs.html
float allfreqs[100] = {
//C      C#       D        Eb       E         F        F#       G        Ab       A       Bb        B
16.35,   17.32,   18.35,   19.45,   20.60,   21.83,   23.12,   24.50,   25.96,   27.50,   29.14,   30.87,   // 0
32.70,   34.65,   36.71,   38.89,   41.20,   43.65,   46.25,   49.00,   51.91,   55.00,   58.27,   61.74,   // 12
65.41,   69.30,   73.42,   77.78,   82.41,   87.31,   92.50,   98.00,   103.83,  110.00,  116.54,  123.47,  // 24
130.81,  138.59,  146.83,  155.56,  164.81,  174.61,  185.00,  196.00,  207.65,  220.00,  233.08,  246.94,  // 36
261.63,  277.18,  293.66,  311.13,  329.63,  349.23,  369.99,  392.00,  415.30,  440.00,  466.16,  493.88,  // 48
523.25,  554.37,  587.33,  622.25,  659.26,  698.46,  739.99,  783.99,  830.61,  880.00,  932.33,  987.77,  // 60
1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53, // 72
2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07, // 84
4186.01, 4434.92, 4698.64, 4978.03};                                                                        // 96
 


void arpeggiate_orig(int note1, int note2, int sustain, int postdelay)
{ 
     unsigned long now = micros();
     unsigned long notestart = now;
     unsigned long noteend = now + (unsigned long) sustain * 1000ul;
     unsigned long ms1 = (unsigned long) ((1.0 / allfreqs[note1]) * 1000000.0) / 2; 
     unsigned long ms2 = (unsigned long) ((1.0 / allfreqs[note2]) * 1000000.0) / 2;
     
     setLights( (1 << (note2 % 12)) | (1 << (note1 % 12)) );

     while (now < noteend) 
     {
       /* Simple square wave.  Should I be on or off? */
        if (((now - notestart) / ( now & 0x00008000 ? ms1 : ms2 ) ) % 2)
          PORTB |= 0x02; // on Uno, equivalent to digialWrite(9, 1) but faster 
        else
          PORTB &= 0xFD; // on Uno, equivalent to digialWrite(9, 0) but faster
        now = micros();
     } 
     setLights(0);
     delay(postdelay);
}   

unsigned long a_attack = 50;  /* milliseconds */ 
unsigned long a_sustain = 160;  /* milliseconds */ 
unsigned long a_release = 20;  /* milliseconds */ 
unsigned long a_delay = 20;   /* milliseconds */ 


void arpeggiate(int note1, int note2)
{ 
     unsigned long now = micros();
     unsigned long notestart = now;
     unsigned long noteend = now;
     unsigned long ms1 = (unsigned long) ((1.0 / allfreqs[note1]) * 1000000.0); 
     unsigned long ms2 = (unsigned long) ((1.0 / allfreqs[note2]) * 1000000.0);
     
     setLights( (1 << (note2 % 12)) | (1 << (note1 % 12)) );

     unsigned long on_ms; 
          
     // attack     
     noteend += a_attack * 1000ul;
     while (now < noteend) 
     {
        unsigned long ms = ( now & 0x00008000 ? ms1 : ms2 ) ; 
            on_ms = ms >> 4;
            
        if ((now - notestart) % ms < on_ms)
          PORTB |= 0x02; // on Uno, equivalent to digialWrite(9, 1) but faster 
        else
          PORTB &= 0xFD; // on Uno, equivalent to digialWrite(9, 0) but faster
        now = micros();
     } 
     // sustain     
     noteend += a_sustain * 1000ul;
     while (now < noteend) 
     {
        unsigned long ms = ( now & 0x00008000 ? ms1 : ms2 ) ; 
            on_ms = ms >> 2;
            
        if ((now - notestart) % ms < on_ms)
          PORTB |= 0x02; // on Uno, equivalent to digialWrite(9, 1) but faster 
        else
          PORTB &= 0xFD; // on Uno, equivalent to digialWrite(9, 0) but faster
        now = micros();
     } 
     // release    
     noteend += a_release * 1000ul;
     while (now < noteend) 
     {
        unsigned long ms = ( now & 0x00008000 ? ms1 : ms2 ) ; 
            on_ms = ms >> 1;
            
        if ((now - notestart) % ms < on_ms)
          PORTB |= 0x02; // on Uno, equivalent to digialWrite(9, 1) but faster 
        else
          PORTB &= 0xFD; // on Uno, equivalent to digialWrite(9, 0) but faster
        now = micros();
     } 
     
     setLights(0);
     delay(a_delay);
}   

#define nC2  24  
#define nCs2 25
#define nD2  26
#define nEb2 27
#define nE2  28
#define nF2  29
#define nFs2 30
#define nG2  31
#define nAb2 32
#define nA2  33
#define nBb2 34
#define nB2  35

#define nC3  36  
#define nCs3 37
#define nD3  38
#define nEb3 39
#define nE3  40
#define nF3  41
#define nFs3 42
#define nG3  43
#define nAb3 44
#define nA3  45
#define nBb3 46
#define nB3  47

#define nC4  48
#define nCs4 49
#define nD4  50
#define nEb4 51
#define nE4  52
#define nF4  53
#define nFs4 54
#define nG4  55
#define nAb4 56
#define nA4  57
#define nBb4 58
#define nB4  59

#define nC5  60
#define nCs5 61
#define nD5  62
#define nEb5 63
#define nE5  64
#define nF5  65
#define nFs5 66
#define nG5  67
#define nAb5 68
#define nA5  69
#define nBb5 70
#define nB5  71

#define nC6  72
#define nCs6 73
#define nD6  74
#define nEb6 75
#define nE6  76
#define nF6  77
#define nFs6 78
#define nG6  79
#define nAb6 80
#define nA6  81
#define nBb6 82
#define nB6  83


void pin9sound()
{ 
  /* see what I sounds can make with a speaker on pin 9 */
  setLights(0);

  delay(1000);  
 // from J. S. Bach, Praeludium II

  a_attack = 50;  /* Allegro 8th note */ 
  a_sustain = 80;  /* milliseconds */ 
  a_release = 40;  /* milliseconds */ 
  a_delay = 10;   /* milliseconds */ 
 
  for (int n = 0; n < 2; n++ ) {
    arpeggiate (nC3,nC5);
    arpeggiate (nG3,nEb4);
    arpeggiate (nF3,nD4);
    arpeggiate (nG3,nEb4);

    arpeggiate (nEb3,nC4);
    arpeggiate (nG3,nEb4);
    arpeggiate (nF3,nD4);
    arpeggiate (nG3,nEb4);
  }  
  for (int n = 0; n < 2; n++ ) {
    arpeggiate (nC3,nAb4);
    arpeggiate (nAb3,nF4);
    arpeggiate (nG3,nE4);
    arpeggiate (nAb3,nF4);

    arpeggiate (nF3,nC4);
    arpeggiate (nAb3,nF4);
    arpeggiate (nG3,nE4);
    arpeggiate (nAb3,nF4);
  }  

  for (int n = 0; n < 2; n++ ) {
    arpeggiate (nC3,nB4);
    arpeggiate (nAb3,nF4);
    arpeggiate (nG3,nEb4);
    arpeggiate (nAb3,nF4);

    arpeggiate (nF3,nD4);
    arpeggiate (nAb3,nF4);
    arpeggiate (nG3,nEb4);
    arpeggiate (nAb3,nF4);
  }  

  for (int n = 0; n < 2; n++ ) {
    arpeggiate (nC3,nC5);
    arpeggiate (nEb3,nG4);
    arpeggiate (nD3,nF4);
    arpeggiate (nEb3,nG4);

    arpeggiate (nG3,nEb4);
    arpeggiate (nEb3,nG4);
    arpeggiate (nD3,nF4);
    arpeggiate (nEb3,nG4);
  }  

  // skip to Adagio -- first note is an 4th, (857ms total)
  a_attack = 60;  /* Adagio 4th note */ 
  a_sustain = 600;  /* milliseconds */ 
  a_release = 80;  /* milliseconds */ 
  a_delay = 20;   /* milliseconds */ 
  arpeggiate (nBb3,nE4);

  a_attack = 15;  /* Adagio 16th note */ 
  a_sustain = 160;  /* milliseconds */ 
  a_release = 20;  /* milliseconds */ 
  a_delay = 10;   /* milliseconds */ 
  arpeggiate (nE4,nE4);
  arpeggiate (nC4,nC4);
  arpeggiate (nD4,nD4);
  arpeggiate (nE4,nE4);
  // 8 32nth notes 
  a_attack = 7;  /* Adagio 32nd note */ 
  a_sustain = 80;  /* milliseconds */ 
  a_release = 10;  /* milliseconds */ 
  a_delay = 5;   /* milliseconds */ 
  arpeggiate (nF4,nF4);
  arpeggiate (nG4,nG4);
  arpeggiate (nAb4,nAb4);
  arpeggiate (nBb4,nBb4);
  arpeggiate (nC5,nC5);
  arpeggiate (nBb4,nBb4);
  arpeggiate (nAb4,nAb4);
  arpeggiate (nG4,nG4);
  // a 16th note
  a_attack = 15;  /* Adagio 16th note */ 
  a_sustain = 160;  /* milliseconds */ 
  a_release = 20;  /* milliseconds */ 
  a_delay = 10;   /* milliseconds */ 
  arpeggiate (nF4,nF4);
  // 2 32nth notes 
  a_attack = 7;  /* Adagio 32nd note */ 
  a_sustain = 80;  /* milliseconds */ 
  a_release = 10;  /* milliseconds */ 
  a_delay = 5;   /* milliseconds */ 
  arpeggiate (nG4,nG4);
  arpeggiate (nE4,nE4);

  // another quarter note  
  a_attack = 60;  /* Adagio 4th note */ 
  a_sustain = 600;  /* milliseconds */ 
  a_release = 80;  /* milliseconds */ 
  a_delay = 20;   /* milliseconds */ 
  arpeggiate (nAb3,nF4);
  // 8 16th notes
  a_attack = 15;  /* Adagio 16th note */ 
  a_sustain = 160;  /* milliseconds */ 
  a_release = 20;  /* milliseconds */ 
  a_delay = 10;   /* milliseconds */ 
  arpeggiate (nF4,nF4);
  arpeggiate (nG4,nG4);
  arpeggiate (nF4,nF4);
  arpeggiate (nE4,nE4);
  arpeggiate (nF4,nF4);
  arpeggiate (nG4,nG4);
  arpeggiate (nAb4,nAb4);
  arpeggiate (nG4,nG4);
  // 8 32nth notes 
  a_attack = 7;  /* Adagio 32nd note */ 
  a_sustain = 80;  /* milliseconds */ 
  a_release = 10;  /* milliseconds */ 
  a_delay = 5;   /* milliseconds */ 
  arpeggiate (nF4,nF4);
  arpeggiate (nEb4,nEb4);
  arpeggiate (nD4,nD4);
  arpeggiate (nEb4,nEb4);
  arpeggiate (nF4,nF4);
  arpeggiate (nD4,nD4);
  arpeggiate (nEb4,nEb4);
  arpeggiate (nF4,nF4);
  
  // allegro 8th notes: 214 ms total
  a_attack = 50;  /* Allegro 8th note */ 
  a_sustain = 80;  /* milliseconds */ 
  a_release = 40;  /* milliseconds */ 
  a_delay = 10;   /* milliseconds */ 

  a_delay = 0;   /* needs to be smoother. */

  arpeggiate (nB3,nB3);
  arpeggiate (nC2,nC2);
  arpeggiate (nB2,nB2);
  arpeggiate (nD3,nD3);
  arpeggiate (nF3,nF3);
  arpeggiate (nAb3,nAb3);
  arpeggiate (nG3,nG3);
  arpeggiate (nF3,nF3);
  arpeggiate (nB3,nB3);
  arpeggiate (nF3,nF3);
  arpeggiate (nD4,nD4);
  arpeggiate (nF3,nF3);
  arpeggiate (nB3,nB3);
  arpeggiate (nAb3,nAb3);
  arpeggiate (nG3,nG3);
  arpeggiate (nF3,nF3);

  arpeggiate (nE3,nE3);
  arpeggiate (nCs4,nCs4);
  arpeggiate (nBb3,nBb3);
  arpeggiate (nG3,nG3);
  arpeggiate (nC4,nC4);
  arpeggiate (nAb3,nAb3);
  arpeggiate (nF3,nF3);
  arpeggiate (nAb3,nAb3);
  arpeggiate (nG3,nG3);
  arpeggiate (nBb3,nBb3);
  arpeggiate (nG3,nG3);
  arpeggiate (nE3,nE3);
  arpeggiate (nAb3,nAb3);
  arpeggiate (nF3,nF3);
  arpeggiate (nD3,nD3);
  arpeggiate (nF3,nF3);

  arpeggiate (nE3,nE3);
  arpeggiate (nG3,nG3);
  arpeggiate (nE3,nE3);
  arpeggiate (nC3,nC3);
  arpeggiate (nF3,nF3);
  arpeggiate (nD3,nD3);
  arpeggiate (nB2,nB2);
  arpeggiate (nD3,nD3);
  arpeggiate (nC2,nC2);
  arpeggiate (nG2,nG2);
  arpeggiate (nC3,nC3);
  arpeggiate (nC3,nD3);

    // slow it down
  a_attack += a_attack / 10;
  a_sustain += a_sustain / 10;
  a_release += a_release / 10;

  arpeggiate (nC3,nE3);
  arpeggiate (nG3,nG3);
  arpeggiate (nBb3,nBb3);
  arpeggiate (nG3,nG3);

  // skip to the last measure 
    // slow it down
  a_attack += a_attack / 10;
  a_sustain += a_sustain / 10;
  a_release += a_release / 10;


  arpeggiate (nC3,nAb3);
  arpeggiate (nC4,nC4);
  arpeggiate (nF4,nF4);
  arpeggiate (nD4,nD4);
 
  a_attack += a_attack / 10;
  a_sustain += a_sustain / 10;
  a_release += a_release / 10;
  

  arpeggiate (nF4,nF4);
  arpeggiate (nAb4,nAb4);
  arpeggiate (nC5,nC5);
  arpeggiate (nB4,nB4);

  a_attack += a_attack / 10;
  a_sustain += a_sustain / 10;
  a_release += a_release / 10;

  arpeggiate (nC5,nC5);
  arpeggiate (nG4,nG4);
  arpeggiate (nF4,nF4);
  arpeggiate (nD4,nD4);

  a_sustain = 1000;  /* milliseconds */ 
  a_delay=2000;

  arpeggiate (nC3,nE4);

}     
   
 

void loop()
{ 
           attract_fadeout();
           pin9sound();
           hardwarePWM();
           pwmchase();
}   
   
 
    
  
