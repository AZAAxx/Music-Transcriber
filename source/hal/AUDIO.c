#include "AUDIO.h"
#include "../address-map.h"
#include <math.h>

#define f_s 8000
#define T_s 1/f_s

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


void analyze_audio_continuous(int tempo){

    // tempo is BPM, beats per minute, specifically quarter notes per minute
    double duration_quarter = 60/tempo;
    //double duration_eighth = 30/tempo;

    // the sensitivity is for now only quarter notes
    int total_samples = duration_quarter/T_s;
    int samples = 0;
    double * audio_input = malloc(total_samples * sizeof(double));

    while(1){

        //get the audio samples 
        while (samples < total_samples) {
            if (isFIFOavailable()) {

                int voltage = fmax(*(AUDIO_BASE + 2), *(AUDIO_BASE + 3));    // get fmax to make it more foolproof
                audio_input[samples] = voltage;                              // save it in array

                samples++;
            }
        }


        // process the audio to get the note
        char * note = get_fft_result(audio_input, samples);
        printf("%s\n", note);
    }

}
