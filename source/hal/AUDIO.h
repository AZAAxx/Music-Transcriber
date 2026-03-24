#ifndef __AUDIO__
#define __AUDIO__

#define T_SAMPLE 125e-6
#define FREQ_SAMPLE 8000

void AUDIO_init();        // use to set up the AUDIO 

int isFIFOavailable();  // use to check the WSRC, WSLC, RARC, and RALC values

void play_frequency(double frequency, double volume, double duration);

#endif