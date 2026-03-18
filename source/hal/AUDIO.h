#ifndef __AUDIO__
#define __AUDIO__

#define T_SAMPLE 125e-6
#define FREQ_SAMPLE 8000

volatile int * AUDIO_BASE;

void __init__();        // use to set up the AUDIO 

void __deinit__();      // use to disble the AUDIO

int isFIFOavailable();  // use to check the WSRC, WSLC, RARC, and RALC values

#endif