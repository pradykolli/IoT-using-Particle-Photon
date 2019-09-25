//SYSTEM_THREAD(ENABLED)
SYSTEM_MODE(MANUAL)

#include "SparkIntervalTimer.h"
#include <math.h>

const int MIDPOINT = 2048;                  // zenter point for DAC
const int MAX_VOL  = 1600;                  // amplitude around (+/-) center point (no more than 2047! to avoid clipping)
const int SAMPLE_PERIODE = 1000000/44100;   // µs between samples (44.1kHz)
const int SAMPLES = 50;                   
uint16_t  sine[SAMPLES];                    // one periode over 50 samples is aprox. 880Hz 

volatile int r = 0;                         // sample to play on right channel
volatile int l = 25;                        // sample to play on left channel (slightly offset)

IntervalTimer tPlayer;

void setup() {
  pinMode(DAC1, OUTPUT);
  pinMode(DAC2, OUTPUT);
  
  for (int i=0; i < SAMPLES; i++)
  { // precalc one periode sine wave
    double x = 2.0 * M_PI * i / SAMPLES;
    sine[i] = MIDPOINT + MAX_VOL * sin(x); 
  }
  
  tPlayer.begin(playSample, SAMPLE_PERIODE, uSec);
}

void loop() {
}

void playSample()
{
    analogWrite(DAC1, sine[r++]);
    analogWrite(DAC2, sine[l++]);
    
    r %= SAMPLES;
    l %= SAMPLES;
}
