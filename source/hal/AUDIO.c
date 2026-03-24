#include "AUDIO.h"
#include <time.h>

void AUDIO_init(){
    volatile int * AUDIO_BASE = (int*) AUDIO_BASE;
    *(AUDIO_BASE) = 0b1100;    // set the control register
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

    int audio_counters, WSC;
    int period, num_samples, counter;
    
    period = 1/frequency;                              //calulate period and number of samples in a period
    float t_sample = 125/1000000;
    num_samples = period / t_sample;

    counter = num_samples/2;                           //store the counter initial value
    
    time_t t_begin = time(NULL);
    time_t t = t_begin;
    while(difftime(t_begin, t) < duration){

        if(isFIFOavailable()){                         //check that there's space in FIFO
            *(AUDIO_BASE + 2) = volume;                //set the left and right FIFOs to val
            *(AUDIO_BASE + 3) = volume;     
        }

        counter--;                                     //decrement counter
        if(counter == 0) {                             //restart the counter and invert val if counter == 0
            volume = -volume;
            counter = num_samples/2;
        }
        
        t = time(NULL);
    }
}

