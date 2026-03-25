#include "AUDIO.h"
#include "../address-map.h"
#include <time.h>

void AUDIO_init(){
    volatile int * audio_ptr = AUDIO_BASE;
    *(audio_ptr) = 0x8;   // set CW bit to clear/reset the FIFOs first
    *(audio_ptr) = 0x0;   // then clear it to normal
}


int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);        //load audio base register
    //RAC = audio_counters & 0xFF;                   
    int WSC = (audio_counters >> 16) & 0xFF;       //extract WSC and RAC value
    int RAC = audio_counters & 0xFF;               //assume left and right FIFO have the same counts

    if(WSC > 0 & RAC > 0) return 1;                //check that there's space in FIFOs
    return 0;                           
}

void play_frequency(double frequency, double volume, double duration){
    double t_sample = 125.0 / 1000000.0;
    int half_period_samples = (int)((1.0 / frequency / 2.0) / t_sample);
    if (half_period_samples < 1) half_period_samples = 1;
    int total_samples = (int)(duration / t_sample);

    int counter = 0;
    int sign = 1;
    int samples_written = 0;

    while (samples_written < total_samples) {
        if (isFIFOavailable()) {
            *(AUDIO_BASE + 2) = (int)(sign * volume);
            *(AUDIO_BASE + 3) = (int)(sign * volume);
            counter++;
            samples_written++;
            if (counter >= half_period_samples) {
                sign = -sign;
                counter = 0;
            }
        }
    }
}

