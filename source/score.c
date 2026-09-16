#include "hal/VGA.h"
#include "hal/AUDIO.h"
#include "address-map.h"
#include "score.h"
#include "VGA.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SW_BASE         0xFF200040
#define KEY_BASE        (volatile int *) 0xFF200050
#define AUDIO_BASE      (volatile int *)0xFF203040
#define PI              3.14159265358979324

const int NOTE_WIDTH = 7; // this many pixels
const short int TOOLBAR_COLOR = 0x731F;

const int VERT_MIN = 0;
const int VERT_MAX = 239;
const int HOR_MIN = 0;
const int HOR_MAX = 319;

int current_hor;
int current_vert;

volatile unsigned int *SW = (unsigned int*)SW_BASE;

int staff_center;
char note_type;
bool note_drawn = false;


void draw_score(Score* score);
void play_score(Score* score);

void analyze_audio_continuous(struct Score * scr);

void score(Score* score) {
    AUDIO_init();
    VGA_init();
    draw_score(score);

    int edge_cap;

    while (1) { 
        unsigned int sw = *SW & 0x3FF;

        if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3);
            if (edge_cap & 0x1) {
                *(KEY_BASE + 3) = 0x3FF;
                draw_score(score);
            }
            if (edge_cap & 0x2) {
                *(KEY_BASE + 3) = 0x3FF;
                play_score(score);
            }
            if (sw & 0x2) {
                analyze_audio_continuous(score);
                // printf("calling analyze_audio_continuous()...\n");
            }
            if (edge_cap & 0x8) {
                *(KEY_BASE + 3) = 0x3FF;
                terminal();
            }
        }
        *(KEY_BASE + 3) = 0x3FF;
    }
}

void draw_score_helper(Note * note){

    char duration = note->duration;
    char pitch = note->note;
    int octave = note->octave;
    bool is_sharp = note->is_sharp;

    note_type = duration;

    if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23)) {
        if ((pitch == 'C') && (octave == 4)) {
            draw_ledger_line(current_hor, current_vert);
        }
        else if ((pitch == 'B') && (octave == 3)) {
            draw_ledger_line(current_hor, current_vert - 5);
        }
        else if ((pitch == 'A') && (octave == 5)) {
            draw_ledger_line(current_hor, current_vert);
        }
        else if ((pitch == 'B') && (octave == 5)) {
            draw_ledger_line(current_hor, current_vert + 5);
        }
        else if ((pitch == 'C') && (octave == 6)) {
            draw_ledger_line(current_hor, current_vert);
            draw_ledger_line(current_hor, current_vert + 9);
        }
    }

    if (is_sharp) draw_sharp(current_hor - 15, current_vert - 5);
        
    if      (note_type == 'w') draw_whole_note(current_hor, current_vert);
    else if (note_type == 'h') draw_half_note(current_hor, current_vert);
    else if (note_type == 'q') draw_quarter_note(current_hor, current_vert);
    else if (note_type == 'e') draw_eighth_note(current_hor, current_vert);
    else if (note_type == 's') draw_sixteenth_note(current_hor, current_vert);
    
}

void draw_score(Score* score){
	// handles drawing the whole score on the page
    // draws the score using different functions for drawing notes
    // draw each note here and call it once in the main function
    background(WHITE);
    draw_staff(15, 30);
    draw_time_signature(32, 30);
    draw_staff(15, 110);
    draw_staff(15, 190);
    draw_bar_line(HOR_MAX - 15 - 2, 190);
    draw_bar_line(HOR_MAX - 15 - 4, 190);
	
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
	
    background(WHITE);
    draw_staff(15, 30);
    draw_time_signature(32, 30);
    draw_staff(15, 110);
    draw_staff(15, 190);
    draw_bar_line(HOR_MAX - 15 - 2, 190);
    draw_bar_line(HOR_MAX - 15 - 4, 190);

    current_hor = 60;
    current_vert = 30 + 27;
    staff_center = 30 + 18;

    // score title
    CURSOR_X = 10;
    write(score->name, BLACK);

    // score tempo
    CURSOR_X = 230;
    char tempo_str[20] = "BPM ";
    int tempo = score->tempo;
    int i = 4; // start concatenating after "BPM "
    int start = i;

    if (tempo == 0) {
        tempo_str[i++] = '0';
    } else {
        while (tempo > 0) {
            tempo_str[i++] = '0' + (tempo % 10);
            tempo /= 10;
        }
        // reverse the digits
        int end = i - 1;
        while (start < end) {
            char tmp = tempo_str[start];
            tempo_str[start++] = tempo_str[end];
            tempo_str[end--] = tmp;
        }
    }
    tempo_str[i] = '\0';
    write(tempo_str, BLACK);

    if (score->notes == NULL || score->notes->note == '\0') return;

    Note* current_note = score->notes;
    while (current_note != NULL) {
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;

        if (pitch == '\0') break;
        
        note_type = duration;

        // check if going off screen
        if      (duration == 'w') {
            if ((current_hor + 120) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
                staff_center += (80);
            }
        }
        else if (duration == 'h') {
            if ((current_hor + 60) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
                staff_center += (80);
            }
        }
        else {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
                staff_center += (80);
            }
        }

        if      ((pitch == 'B') && (octave == 3)) current_vert = staff_center + 32;
        else if ((pitch == 'C') && (octave == 4)) current_vert = staff_center + 27;
        else if ((pitch == 'D') && (octave == 4)) current_vert = staff_center + 23;
        else if ((pitch == 'E') && (octave == 4)) current_vert = staff_center + 18;
        else if ((pitch == 'F') && (octave == 4)) current_vert = staff_center + 13;
        else if ((pitch == 'G') && (octave == 4)) current_vert = staff_center + 9;
        else if ((pitch == 'A') && (octave == 4)) current_vert = staff_center + 5;
        else if ((pitch == 'B') && (octave == 4)) current_vert = staff_center;
        else if ((pitch == 'C') && (octave == 5)) current_vert = staff_center - 5;
        else if ((pitch == 'D') && (octave == 5)) current_vert = staff_center - 9;
        else if ((pitch == 'E') && (octave == 5)) current_vert = staff_center - 14;
        else if ((pitch == 'F') && (octave == 5)) current_vert = staff_center - 18;
        else if ((pitch == 'G') && (octave == 5)) current_vert = staff_center - 23;
        else if ((pitch == 'A') && (octave == 5)) current_vert = staff_center - 27;
        else if ((pitch == 'B') && (octave == 5)) current_vert = staff_center - 32;
        else if ((pitch == 'C') && (octave == 6)) current_vert = staff_center - 36;


        draw_score_helper(current_note);

        swap_buffers_on_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);

        draw_score_helper(current_note);

        if (note_type == 'w') current_hor += 120;
        else if (note_type == 'h') current_hor += 60;
        else if (note_type == 'q') current_hor += 30;
        else if (note_type == 'e') current_hor += 30;
        else if (note_type == 's') current_hor += 30;
        
        current_note = current_note->next;
    }
}


void play_score(Score* score){
    Note* current_note = score->notes;
    while (current_note != NULL) {
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
        double frequency = 0.0;
        double dur = 0.0;
        int bpm = score->tempo;
        double secs_per_beat = 60.0 / ((double) bpm);
        bool is_sharp = current_note->is_sharp;

        if (pitch == '\0') break;

        if (pitch != '\0') {
            if      (duration == 'w') dur = secs_per_beat * 4;
            else if (duration == 'h') dur = secs_per_beat * 2;
            else if (duration == 'q') dur = secs_per_beat;
            else if (duration == 'e') dur = secs_per_beat / 2;
            else if (duration == 's') dur = secs_per_beat / 4;

        if      ((pitch == 'C') && (octave == 4) && !is_sharp) frequency = 261.63;
        else if ((pitch == 'C') && (octave == 4) && is_sharp)  frequency = 277.18; 
        else if ((pitch == 'D') && (octave == 4) && !is_sharp) frequency = 293.66;
        else if ((pitch == 'D') && (octave == 4) && is_sharp)  frequency = 311.13;
        else if ((pitch == 'E') && (octave == 4))              frequency = 329.63;
        else if ((pitch == 'F') && (octave == 4) && !is_sharp) frequency = 349.23;
        else if ((pitch == 'F') && (octave == 4) && is_sharp)  frequency = 369.99;
        else if ((pitch == 'G') && (octave == 4) && !is_sharp) frequency = 392.00;
        else if ((pitch == 'G') && (octave == 4) && is_sharp)  frequency = 415.30;
        else if ((pitch == 'A') && (octave == 4) && !is_sharp) frequency = 440.00;
        else if ((pitch == 'A') && (octave == 4) && is_sharp)  frequency = 466.16;
        else if ((pitch == 'B') && (octave == 4))              frequency = 493.88;
        else if ((pitch == 'C') && (octave == 5) && !is_sharp) frequency = 523.25;
        else if ((pitch == 'C') && (octave == 5) && is_sharp)  frequency = 554.37;
        else if ((pitch == 'D') && (octave == 5) && !is_sharp) frequency = 587.33;
        else if ((pitch == 'D') && (octave == 5) && is_sharp)  frequency = 622.25;
        else if ((pitch == 'E') && (octave == 5))              frequency = 659.25;
        else if ((pitch == 'F') && (octave == 5) && !is_sharp) frequency = 698.46;
        else if ((pitch == 'F') && (octave == 5) && is_sharp)  frequency = 739.99;
        else if ((pitch == 'G') && (octave == 5) && !is_sharp) frequency = 783.99;
        else if ((pitch == 'G') && (octave == 5) && is_sharp)  frequency = 830.61;
        else if ((pitch == 'A') && (octave == 5) && !is_sharp) frequency = 880.00;
        else if ((pitch == 'A') && (octave == 5) && is_sharp)  frequency = 932.33;
        else if ((pitch == 'B') && (octave == 5))              frequency = 987.77;
        else if ((pitch == 'C') && (octave == 6))              frequency = 1046.50;
        else if ((pitch == 'B') && (octave == 3))              frequency = 246.94;
        }

        double volume = 0x7FFFFFF;
        play_frequency(frequency, volume, dur);
        play_frequency(0, volume, 0.1);

        current_note = current_note->next;
    }
}