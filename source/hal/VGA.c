#include "../GLOBALS.h"
#include "VGA.h"

void __init__(){
    volatile int * pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;            // first store the address in the  back buffer
    swap_buffers_on_vsync();                           // swap the front/back buffers, to set the front buffer location
    pixel_buffer_start = *pixel_ctrl_ptr;              // set pixel_buffer_start to use in clear_screen()
    background(BLACK);                                 // clear the front buffer


    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);        // we draw on the back buffer
    background(BLACK); 
}



void background(int color){                            // iterate through every x, y
    for(int x = 0; x < 320; x++){
        for(int y = 0; y < 240; y++){
            plot_pixel(x, y, color);                   // paint it black
        }
    }
}



void plot_pixel(int x, int y, short int color){
    volatile short int *one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = color;
}



void swap_buffers_on_vsync() {
    volatile int * pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;
    *pixel_ctrl_ptr = 1;                                // write 1 into the buffer reg to request a swap
    while (*(pixel_ctrl_ptr + 3) & 0x1);                // Wait until status.S turns 0
}

