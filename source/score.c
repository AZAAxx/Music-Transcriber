#include "hal/VGA.h"
#include "GLOBALS.h"
#include "score.h"

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

