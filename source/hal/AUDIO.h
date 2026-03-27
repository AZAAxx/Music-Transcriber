#ifndef __AUDIO__
#define __AUDIO__

#include "database.h"

#define T_SAMPLE 125e-6
#define FREQ_SAMPLE 8000

#define f_s 8000
#define T_s 1/f_s
#define PI 3.1415926535


// use to set up the AUDIO
void AUDIO_init();         

// use to check the WSRC, WSLC, RARC, and RALC values
int isFIFOavailable();  

// sends the audio FIFO a square wave signal corresponding to 'frequency' for 'duration'
void play_square_wave(double frequency, double volume, double duration);

// send the FIFO values of a sine wave
void play_frequency(double frequency, double amplitude, double duration);

// continuosly analyzes the FIFO input and writes corresponding notes to the Score scr
void analyze_audio_continuous(struct Score * scr);

#endif