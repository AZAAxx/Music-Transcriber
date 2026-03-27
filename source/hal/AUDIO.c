#include "AUDIO.h"
#include "../address-map.h"
#include "../database.h"
#include <math.h>


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

void play_square_wave(double frequency, double volume, double duration){
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


void play_frequency(double frequency, double amplitude, double duration){
    double period = 1 / frequency;
    double N = period * f_s;                      // this is the number of samples in a period, NOT an integer
    int total_samples = (int)(duration * f_s);
    int k = 0;                                    // written sample count

    // x[n] = A * sin(2PI/N * k)

    while (k < total_samples) {
        if (isFIFOavailable()) {
            int voltage = amplitude * sin(2 * PI * k / N);
            k++;
            *(AUDIO_BASE + 2) = voltage;
            *(AUDIO_BASE + 3) = voltage;
        }
    }
}





void analyze_audio_continuous(struct Score * scr){

    int tempo = scr->tempo;                             // tempo is BPM, beats per minute, specifically quarter notes per minute

    double duration_quarter = (double) 60/tempo;
    double duration_eighth = (double) 30/tempo;
    
    int total_samples = duration_eighth * f_s;           // the sensitivity is for now only quarter notes !!!
    int k = 0;                                          // the number of samples written to audio_input

    int * audio_input = malloc(total_samples * sizeof(int));
    int right, left;

    int edge_cap = *(KEY_BASE + 3); 
    bool run = edge_cap & 0x8;         // start running if KEY[3] pressed
    *(KEY_BASE + 3) = 0x3FF;           // reset edge capture register
    
    while(run){ // starts and stops depending on KEY[3]

        //get the audio samples 
        while (k < total_samples) {
            if (isFIFOavailable()) {

                right = *(AUDIO_BASE + 2);
                left = *(AUDIO_BASE + 3);

                int voltage = fmax(right, left);   // get fmax to make it more foolproof
                audio_input[k] = voltage;          // save it in array
                k++;
            }
        }
        
        char * note = get_fft_result(audio_input, k);    // process the audio to get the note
        printf("%s\n", note);                            // print the audio (for now)

        // add the note to score
        Note * new_note = malloc(sizeof(Note));
        new_note->note = note[0];
        new_note->octave = note[1] - '0';
        new_note->duration = 'e';
        new_note->next = NULL;

        add_note(new_note, scr);


        // optimize the notes by merging them




        // get KEY edgecapture register 
        edge_cap = *(KEY_BASE + 3); 
        bool run = !(edge_cap & 0x8);      // STOP running if KEY[3] pressed
        *(KEY_BASE + 3) = 0x3FF;           // reset edge capture register
    }

}
