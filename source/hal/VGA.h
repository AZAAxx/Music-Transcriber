//Hardware level display helpers


#ifndef __VGA__
#define __VGA__

#include "../address-map.h"


int CURSOR_X;                                 // the values for the cursor baseline, the bottom left of the line
int CURSOR_Y;
int CURSOR_X_DEFAULT;

volatile int * pixel_ctrl_ptr;
volatile int * pixel_buffer_start;              // global variable
short int Buffer1[240][512];                  // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];


void swap_buffers_on_vsync();

void plot_pixel(int x, int y, short int color);

void background(int color);

void VGA_init();


/* by default these functions keep track of where the curcor is. If you want to write to 
a different pixel, change CURSOR_X and CURSOR_Y variables before calling the function */

void draw(int* deltaP, int X, int Y);

void draw_char(const GFXfont *font, char c);

void write(const GFXfont *font, const char *str);

void mouse(int X, int Y);

void scroll();






#endif