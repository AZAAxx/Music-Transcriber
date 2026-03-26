#ifndef __AUDIO__
#define __AUDIO__

#include <../GLOBALS.h>

#define T_SAMPLE 125e-6
#define FREQ_SAMPLE 8000

// use to set up the AUDIO
void AUDIO_init();         

// use to check the WSRC, WSLC, RARC, and RALC values
int isFIFOavailable();  

// sends the audio FIFO a square wave signal corresponding to 'frequency' for 'duration'
void play_frequency(double frequency, double volume, double duration);

// continuosly analyzes the FIFO input and writes corresponding notes to the Score scr
void analyze_audio_continuous(struct Score * scr);

#endif