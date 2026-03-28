#include "hal/VGA.h"
#include "hal/AUDIO.h"
#include "address-map.h"
#include "score.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void draw_score(Score* score);
void play_score(Score* score);

bool note_drawn = false;

void score(Score* score) {
    AUDIO_init();

    pixel_ctrl_ptr = (volatile int *)0xFF203020;

    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;
    swap_buffers_on_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    background(WHITE);

    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); 
    draw_score(score);
    
    int edge_cap;
	
    while (1) {
        unsigned int sw = *SW & 0x3FF;
		
        if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3);
            // *(KEY_BASE + 3) = 0x3FF;
            if (edge_cap & 0x1) {
                draw_score(score);
            }
            if (edge_cap & 0x2) {
                play_score(score);
            }
            if (edge_cap & 0x4) {
                //analyze_audio_continuous();
            }
            if (edge_cap & 0x8) {
                *(KEY_BASE + 3) = 0x3FF;
                terminal();
            }
        }
		*(KEY_BASE + 3) = 0x3FF;
    }
}

void draw_score(Score* score){
	// handles drawing the whole score on the page
    // draws the score using different functions for drawing notes
    // draw each note here and call it once in the main function
    background(WHITE);
	
    draw_staff(15, 30);
    draw_time_signature(32, 30);
    // draw_toolbar();
	draw_staff(15, 110);
	draw_staff(15, 190);
	draw_bar_line(HOR_MAX - 15 - 2, 190);
	draw_bar_line(HOR_MAX - 15 - 4, 190);
	
    //swap_buffers_on_vsync();
    //pixel_buffer_start = *(pixel_ctrl_ptr + 1); 
	
    current_hor = 60;
    current_vert = 30 + 27;
    staff_center = 30 + 18;


    for (int note_idx = 0; note_idx < 64; note_idx++) { // note_idx for note array
        // read the duration here instead of edge_cap
		Note* current_note = &score->notes[note_idx];
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
		
        if (pitch == '\0') break;

        note_drawn = true;
        if      (duration == 'w') note_type = 'w';
        else if (duration == 'h') note_type = 'h';
        else if (duration == 'q') note_type = 'q';
        else if (duration == 'e') note_type = 'e';
        else if (duration == 's') note_type = 's';
		
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
        else if (duration == 'q') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 'e') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 's') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }

		// read note here (note and octave together)
        if      ((pitch == 'C') && (octave == 4)) current_vert = staff_center + 27;
        // idea for accidentals put accidental as member of Note struct
        // read if sharp or flat and draw those --> need graphics for this
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
		// end checking note and octave
		
		// keep this
        draw_staff(15, 30);
        draw_time_signature(32, 30);
        // draw_toolbar();
		draw_staff(15, 110);
		draw_staff(15, 190);
		draw_bar_line(HOR_MAX - 15 - 2, 190);
		draw_bar_line(HOR_MAX - 15 - 4, 190);
		
		// keep note_drawn thing
    	// add more notes to this
        if (note_drawn) {
			// add ledger line function for anything that needs it
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23))
                draw_ledger_line(current_hor, current_vert);
            // end ledger line block
			
			// read note duration here again from note_type which is set from duration
			if      (note_type == 'w') draw_whole_note(current_hor, current_vert);
            else if (note_type == 'h') draw_half_note(current_hor, current_vert);
            else if (note_type == 'q') draw_quarter_note(current_hor, current_vert);
            else if (note_type == 'e') draw_eighth_note(current_hor, current_vert);
            else if (note_type == 's') draw_sixteenth_note(current_hor, current_vert);
        }
		// end of note drawing block
		
		// keep this
        swap_buffers_on_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); 

		// this should be the same as the other if statement with (note_drawn) except with incrementing current values
        if (note_drawn) {
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23))
                draw_ledger_line(current_hor, current_vert);
            if (note_type == 'w') {
                draw_whole_note(current_hor, current_vert);
                current_hor += 120;
            }
            else if (note_type == 'h') {
                draw_half_note(current_hor, current_vert);
                current_hor += 60;
            }
            else if (note_type == 'q') {
                draw_quarter_note(current_hor, current_vert);
                current_hor += 30;
            }
            else if (note_type == 'e') {
                draw_eighth_note(current_hor, current_vert);
                current_hor += 30;
            }
            else if (note_type == 's') {
                draw_sixteenth_note(current_hor, current_vert);
                current_hor += 30;
            }
            note_drawn = false;
        }
		// end of note drawing block
    }
}


void play_score(Score* score){
    // take the score and generate frequencies based on notes, play for specified duration
    for (int note_idx = 0; note_idx < 64; note_idx++) { // note_idx for note array
        // read the duration here instead of edge_cap
        Note* current_note = &score->notes[note_idx];
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
        double frequency = 0.0;
        double dur = 0.0; // name dur because something already named duration
        // also assuming 120bpm right now so 1/120 = 0.008333333333s
        int bpm = 120;
        double secs_per_beat = 60.0 / ((double) bpm);
        
        if (pitch != '\0') { // if note exists
			if (duration == 'w') {
				dur = secs_per_beat * 4;
			}	
            else if (duration == 'h') {
				dur = secs_per_beat * 2;	
			}
			else if (duration == 'q') {
				dur = secs_per_beat;	
			}
			else if (duration == 'e') {
				dur = secs_per_beat / 2;
			}
			else if (duration == 's') {
				dur = secs_per_beat / 4;
			}
				
            // read note here (note and octave together) and get frequency
			if ((pitch == 'C') && (octave == 4)) { // C4
				frequency = 261.63;
			}	
			if ((pitch == 'D') && (octave == 4)) { // D4
				frequency = 293.66;
	    	}
			if ((pitch == 'E') && (octave == 4)) { // E4
				frequency = 329.63;
			}	
			if ((pitch == 'F') && (octave == 4)) { // F4
				frequency = 349.23;
			}
			if ((pitch == 'G') && (octave == 4)) { // G4
                frequency = 392.00;
			}
			if ((pitch == 'A') && (octave == 4)) { // A4
                frequency = 440.00;
			}
			if ((pitch == 'B') && (octave == 4)) { // B4
                frequency = 493.88;
			}
			if ((pitch == 'C') && (octave == 5)) { // C5
                frequency = 523.25;
			}
            if ((pitch == 'D') && (octave == 5)) { // D5
                frequency = 587.33;
	    	}
			if ((pitch == 'E') && (octave == 5)) { // E5
                frequency = 659.25;
			}	
			if ((pitch == 'F') && (octave == 5)) { // F5
                frequency = 698.46;
			}
			if ((pitch == 'G') && (octave == 5)) { // G5
                frequency = 783.99;
			}
			if ((pitch == 'A') && (octave == 5)) { // A5
                frequency = 880.00;
			}
			if ((pitch == 'B') && (octave == 5)) { // B5
                frequency = 987.77;
			}
			if ((pitch == 'C') && (octave == 6)) { // C6
                frequency = 1046.50;
			}
        }
        // end checking note and octave
		
        // generate frequency and feed to audio when audio is ready
        double volume = 0x7FFFFF; // max: 0x7FFFFF; min: 0x800000
        play_frequency(frequency, volume, dur);
        play_frequency(0, volume, 0.1);
	}
}