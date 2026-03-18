#include "hal/VGA.h"
#include "GLOBALS.h"
#include "score.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void score(struct Score* scr){
    draw(toolbar, 0, 0);

    draw(staff, 20, 30);           //random numbers for now
    draw(treble_cleff, 20, 30);
    draw(bass_cleff, 40, 30);

    draw(staff, 20, 150); 
    /*more staff and cleffs...*/

    draw_notes(scr);

    //after this we would wait for interrupts
}

void draw_notes(struct Score* scr){

}


int main() {
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;

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
		
		if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3); // checking for any if any keys pressed
            if (edge_cap & 0xF) { // if any KEY[3:0] pressed
				note_drawn = true;
				if (edge_cap & 0x1) {
					note_type = 'w';
				}	
				else if (edge_cap & 0x2) {
					note_type = 'q';	
				}
				else if (edge_cap & 0x4) {
					note_type = 'e';
				}
				else if (edge_cap & 0x8) {
					note_type = 's';
				}
				
				if (sw & 0x2) { // SW[1] = C
					current_vert = staff_center + 27;
				}	
				if (sw & 0x4) { // SW[2] = D
					current_vert = staff_center + 23;
				}
				if (sw & 0x8) { // SW[3] = E
					current_vert = staff_center + 18;
				}	
				if (sw & 0x10) { // SW[4] = F
					current_vert = staff_center + 13;
				}
				if (sw & 0x20) { // SW[5] = G
					current_vert = staff_center + 9;
				}
				if (sw & 0x40) { // SW[6] = A
					current_vert = staff_center + 5;
				}
				if (sw & 0x80) { // SW[7] = B
					current_vert = staff_center;
				}
				if (sw & 0x100) { // SW[8] = C but higher octave
					current_vert = staff_center - 5;
				}
            }
        }  
		
		*(KEY_BASE + 3) = 0x3FF; // reset edge capture register
		
		//background(WHITE);
		draw_staff(15, 30);
		draw_time_signature(32, 30);
		draw_toolbar();
		
		if (note_drawn) {
            if (sw & 0x2) {
                draw_ledger_line(current_hor, current_vert);
            }
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
				
		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

		if (note_drawn) {
            if (sw & 0x2) {
                draw_ledger_line(current_hor, current_vert);
            }
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
	}
}