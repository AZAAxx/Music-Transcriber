#ifndef __AUDIO__
#define __AUDIO__

#include "../database.h"

#define f_s 8000
#define PI 3.1415926535


// use to set up the AUDIO
void AUDIO_init();         

// use to check the WSRC, WSLC, RARC, and RALC values
int isFIFOavailable();  

// send the FIFO values of a sine wave
void play_frequency(double frequency, double amplitude, double duration);

// continuosly analyzes the FIFO input and writes corresponding notes to the Score scr
void analyze_audio_continuous(struct Score * scr);

#endif