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
    *(audio_ptr) = 0x8;                          // set CW bit to clear/reset the FIFOs
    *(audio_ptr) = 0x0;                          // then clear it to normal
}


int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);      // load audio base register                
    int WSC = (audio_counters >> 16) & 0xFF;     // extract Write Space (L/R) Channel and Read Available (L/R) Channel values
    int RAC = audio_counters & 0xFF;             // assume left and right FIFO have the same counts

    if(WSC > 0 & RAC > 0) return 1;              // check that there's space in FIFOs
    return 0;                           
}



void play_frequency(double frequency, double volume, double duration){
    double t_sample = 125.0 / 1000000.0;                       // specified by the audio device capabilities
    int total_samples = (int)(duration / t_sample);
    int samples_written = 0;
 
    double phase = 0.0;                                         // used to assign sign of sample 
    double phase_increment = 2.0 * PI * frequency * t_sample;    
    int sign = 1;

    while (samples_written < total_samples) {
        if (isFIFOavailable()) {
            *(AUDIO_BASE + 2) = (int)(sign * volume);           // write the volume value to both leaft and right FIFOs
            *(AUDIO_BASE + 3) = (int)(sign * volume);

            phase += phase_increment;                           // increase phase 2*pi*f*t = wt with every sample written
            if (phase >= PI) {                                  // sign of volume changes every PI increment of phase (every Period/2)
                sign = -sign;
                phase -= PI;
            }

            samples_written++;
        }
    }
}





void analyze_audio_continuous(struct Score * scr){          //contniuously gets audio and performs FFT to get note value

    int tempo = scr->tempo;
    double duration_eighth = (double) 30/tempo;            // calculate duration of an eighth note using tempo value
    int total_samples = duration_eighth * f_s;             // total number of samples needed to store an eighth note
    int k = 0;

    int * audio_input = malloc(total_samples * sizeof(int));  // allocate array to hold integer audio sample values (to be analyzed)
    int right, left;

    draw_circle(310, 5, RED);                              // draw a red circle on screen to show data acquisition started
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    draw_circle(310, 5, RED);
    
    while(1){
        unsigned int sw = *SW & 0x3FF;
        if (!(sw & 0x2)) break;                            // Check SW1, stop analysing if it has been pressed

        k = 0;                                             // stores the number of samples read and stored in audio_input
        while (k < total_samples) {                        // only get (total_samples) number of samples, enough for an eighth note
            if (isFIFOavailable()) {                       // read from FIFOs while theres data available
                right = *(AUDIO_BASE + 2);
                left = *(AUDIO_BASE + 3);
                int voltage = MAX(right, left);            // average left and right FIFOs to ensure external factors have less effect on analysis
                audio_input[k] = voltage;
                k++;
            }
        }
        
        const char * note = get_fft_result(audio_input, k);  // get the most dominant note using the fft function (implementation is in fft.c)

        Note * new_note = malloc(sizeof(Note));            // allocate a new note with this note and assign appropriate values
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

    free(audio_input);                            // free the audio_input array
    draw_score(scr);                              // erase recording circle on both buffers
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    draw_score(scr);
}
