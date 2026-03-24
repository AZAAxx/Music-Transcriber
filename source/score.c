#include "hal/VGA.h"
#include "GLOBALS.h"
#include "address-map.h"
#include "score.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void draw_score(Score* score);
void play_score(Score* score);

int main() {
    volatile int * pixel_ctrl_ptr = (volatile int *)0xFF203020;

    *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // set front pixel buffer to Buffer1, store address in back buffer
    wait_for_vsync(); // swap front/back buffers
    pixel_buffer_start = *pixel_ctrl_ptr; // initialize pointer to pixel
    background(WHITE); // pixel_buffer_start points to the pixel buffer

    *(pixel_ctrl_ptr + 1) = (int) &Buffer2; // back pixel buffer = Buffer2
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // draw on the back buffer
    background(WHITE); // pixel_buffer_start points to the pixel buffer
	
    // initialize score (staff, clef, time signature)
    draw_staff(15, 30);
	draw_time_signature(32, 30);
    draw_toolbar();
	
	wait_for_vsync(); // swap front and back buffers on VGA vertical sync
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

    // setting up keys
    int edge_cap;
	bool note_drawn = false;
	
	// setting up position
    int current_hor = 60;
    int current_vert = 30+27;
	staff_center = 30+18; // temp
	
    // loop which detects new inputs and draws them
    while (1) {
        // detect edge case for button press -> make sure that SW[0] is on too
        unsigned int sw = *SW & 0x3FF; // sw will hold what switches are on or off
		
		if (sw & 0x1) { // keep this thing so that only inputs being read when SW[0] on
            edge_cap = *(KEY_BASE + 3); // checking for any if any keys pressed
            // drawing score
            if (edge_cap & 0x1) { // if KEY[0] pressed
				draw_score(score_input); // score_input is a placeholder score
            }
            // playing back score
            else if (edge_cap & 0x2) { // if KEY[1] pressed
                play_score(score_input);
            }
            *(KEY_BASE + 3) = 0x3FF; // reset edge capture register
        }
	}
}

void draw_score(Score* score){
    // handles drawing the whole score on the page
    // draws the score using different functions for drawing notes
    // draw each note here and call it once in the main function

    for (int note_idx = 0; note_idx < 64; note_idx++) { // note_idx for note array
        // read the duration here instead of edge_cap
        Note* current_note = score.notes[note_idx];
        char duration = current_note.duration;
        char pitch = current_note.note;
        int octave = current_note.octave;
        
        if (pitch != '\0') { // if note exists
			note_drawn = true;
			if (duration == 'w') {
				note_type = 'w';
			}	
            else if (duration == 'h') {
				note_type = 'h';	
			}
			else if (duration == 'q') {
				note_type = 'q';	
			}
			else if (duration == 'e') {
				note_type = 'e';
			}
			else if (duration == 's') {
				note_type = 's';
			}
				
            // read note here (note and octave together)
			if ((pitch == 'C') && (octave == 4)) { // C4
				current_vert = staff_center + 27;
                // idea for accidentals put accidental as member of Note struct
                // read if sharp or flat and draw those --> need graphics for this
			}	
			if ((pitch == 'D') && (octave == 4)) { // D4
				current_vert = staff_center + 23;
	    	}
			if ((pitch == 'E') && (octave == 4)) { // E4
				current_vert = staff_center + 18;
			}	
			if ((pitch == 'F') && (octave == 4)) { // F4
				current_vert = staff_center + 13;
			}
			if ((pitch == 'G') && (octave == 4)) { // G4
				current_vert = staff_center + 9;
			}
			if ((pitch == 'A') && (octave == 4)) { // A4
				current_vert = staff_center + 5;
			}
			if ((pitch == 'B') && (octave == 4)) { // B4
				current_vert = staff_center;
			}
			if ((pitch == 'C') && (octave == 5)) { // C5
				current_vert = staff_center - 5;
			}
            if ((pitch == 'D') && (octave == 5)) { // D5
				current_vert = staff_center - 9;
	    	}
			if ((pitch == 'E') && (octave == 5)) { // E5
				current_vert = staff_center - 14;
			}	
			if ((pitch == 'F') && (octave == 5)) { // F5
				current_vert = staff_center - 18;
			}
			if ((pitch == 'G') && (octave == 5)) { // G5
				current_vert = staff_center - 23;
			}
			if ((pitch == 'A') && (octave == 5)) { // A5
				current_vert = staff_center - 27;
			}
			if ((pitch == 'B') && (octave == 5)) { // B5
				current_vert = staff_center - 32;
			}
			if ((pitch == 'C') && (octave == 6)) { // C6
				current_vert = staff_center - 36;
			}
        }
        // end checking note and octave
        
        // keep this
		// background(WHITE);
		draw_staff(15, 30);
		draw_time_signature(32, 30);
		draw_toolbar();
		
        // keep note_drawn thing
        // add more notes to this
		if (note_drawn) {
            // add ledger line function for anything that needs it
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23)) {
                draw_ledger_line(current_hor, current_vert);
            }
            // end ledger line block

            // read note duration here again from note_type which is set from duration
			if (note_type == 'w') {
				draw_whole_note(current_hor, current_vert);
			}
			else if (note_type == 'h') {
				draw_half_note(current_hor, current_vert);
			}
			else if (note_type == 'q') {
				draw_quarter_note(current_hor, current_vert);
			}
			else if (note_type == 'e') {
				draw_eighth_note(current_hor, current_vert);
			}
			else if (note_type == 's') {
				draw_sixteenth_note(current_hor, current_vert);
			}
		}
        // end of note drawing block
				
        // keep this
		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

        // this should be the same as the other if statement with (note_drawn) except with incrementing current values
        if (note_drawn) {
            // add ledger line function for anything that needs it
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23)) {
                draw_ledger_line(current_hor, current_vert);
            }
            // end ledger line block

            // read note duration here again from note_type which is set from duration
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
        Note* current_note = score.notes[note_idx];
        char duration = current_note.duration;
        char pitch = current_note.note;
        int octave = current_note.octave;
        int frequency;
        
        if (pitch != '\0') { // if note exists
			note_drawn = true;
			if (duration == 'w') {
				note_type = 'w';
			}	
            else if (duration == 'h') {
				note_type = 'h';	
			}
			else if (duration == 'q') {
				note_type = 'q';	
			}
			else if (duration == 'e') {
				note_type = 'e';
			}
			else if (duration == 's') {
				note_type = 's';
			}
				
            // read note here (note and octave together) and get frequency
			if ((pitch == 'C') && (octave == 4)) { // C4
				frequency = 262;
			}	
			if ((pitch == 'D') && (octave == 4)) { // D4
				frequency = 294;
	    	}
			if ((pitch == 'E') && (octave == 4)) { // E4
				frequency = 330;
			}	
			if ((pitch == 'F') && (octave == 4)) { // F4
				frequency = 349;
			}
			if ((pitch == 'G') && (octave == 4)) { // G4
                frequency = 392;
			}
			if ((pitch == 'A') && (octave == 4)) { // A4
                frequency = 440;
			}
			if ((pitch == 'B') && (octave == 4)) { // B4
                frequency = 494;
			}
			if ((pitch == 'C') && (octave == 5)) { // C5
                frequency = 523;
			}
            if ((pitch == 'D') && (octave == 5)) { // D5
                frequency = 587;
	    	}
			if ((pitch == 'E') && (octave == 5)) { // E5
                frequency = 659;
			}	
			if ((pitch == 'F') && (octave == 5)) { // F5
                frequency = 698;
			}
			if ((pitch == 'G') && (octave == 5)) { // G5
                frequency = 784;
			}
			if ((pitch == 'A') && (octave == 5)) { // A5
                frequency = 880;
			}
			if ((pitch == 'B') && (octave == 5)) { // B5
                frequency = 988;
			}
			if ((pitch == 'C') && (octave == 6)) { // C6
                frequency = 1047;
			}
        }
        // end checking note and octave
		
        // generate frequency and feed to audio when audio is ready
        // comment out for now if adding anything
	}
}