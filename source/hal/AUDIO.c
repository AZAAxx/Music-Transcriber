#include "AUDIO.h"
#include "../address-map.h"
#include "../database.h"
#include "VGA.h"
#include <math.h>


#define f_s 8000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
const char * get_fft_result(int * audio_input, int audio_size);

void AUDIO_init(){
    volatile int * audio_ptr = AUDIO_BASE;
    *(audio_ptr) = 0x8;   // set CW bit to clear/reset the FIFOs first
    *(audio_ptr) = 0x0;   // then clear it to normal
}


int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);        //load audio base register                
    int WSC = (audio_counters >> 16) & 0xFF;       //extract WSC and RAC value
    int RAC = audio_counters & 0xFF;               //assume left and right FIFO have the same counts

    if(WSC > 0 & RAC > 0) return 1;                //check that there's space in FIFOs
    return 0;                           
}



void play_frequency(double frequency, double volume, double duration){
    double t_sample = 125.0 / 1000000.0;
    int total_samples = (int)(duration / t_sample);
    int samples_written = 0;

    double phase = 0.0;
    double phase_increment = 2.0 * PI * frequency * t_sample;
    int sign = 1;

    while (samples_written < total_samples) {
        if (isFIFOavailable()) {
            *(AUDIO_BASE + 2) = (int)(sign * volume);
            *(AUDIO_BASE + 3) = (int)(sign * volume);

            phase += phase_increment;
            if (phase >= PI) {
                sign = -sign;
                phase -= PI;
            }

            samples_written++;
        }
    }
}





void analyze_audio_continuous(struct Score * scr){

    int tempo = scr->tempo;
    double duration_eighth = (double) 30/tempo;
    int total_samples = duration_eighth * f_s;
    int k = 0;

    int * audio_input = malloc(total_samples * sizeof(int));
    int right, left;

    draw_circle(310, 5, RED);
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    draw_circle(310, 5, RED);
    
    while(1){
        // check SW1 
        unsigned int sw = *SW & 0x3FF;
        if (!(sw & 0x2)) break;

        k = 0;

        while (k < total_samples) {
            if (isFIFOavailable()) {
                right = *(AUDIO_BASE + 2);
                left = *(AUDIO_BASE + 3);
                int voltage = MAX(right, left);
                audio_input[k] = voltage;
                k++;
            }
        }
        
        const char * note = get_fft_result(audio_input, k);
        //printf("%s\n", note);

        Note * new_note = malloc(sizeof(Note));
        new_note->note = note[0];
        if (note[1] == '#') {
            new_note->is_sharp = true;
            new_note->octave = note[2] - '0';
        } else {
            new_note->is_sharp = false;
            new_note->octave = note[1] - '0';
        }
        new_note->duration = 'e';
        new_note->next = NULL;

        add_note(new_note, scr);

    }

    free(audio_input);

    // erase recording circle on both buffers
    draw_score(scr);
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    draw_score(scr);
}
