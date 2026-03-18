#include "AUDIO.h"


void __init__(){
    volatile int * AUDIO_BASE = (int*) AUDIO_BASE;
    *(AUDIO_BASE) = 0b1100;    // set the control register
}


void __deinit__(){}

int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);        //load audio base register
    //RAC = audio_counters & 0xFF;                   
    int WSC = (audio_counters >> 16) & 0xFF;       //extract WSC and RAC value
    int RAC = audio_counters & 0xFF;               //assume left and right FIFO have the same counts

    if(WSC > 0 & RAC > 0) return 1;                //check that there's space in FIFOs
    return 0;                           
}