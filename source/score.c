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
    draw_toolbar();
	
    while (1) {
        // detect edge case for button press -> make sure that SW[0] is on too

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}