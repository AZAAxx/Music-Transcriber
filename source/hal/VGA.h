//Hardware level display helpers


#ifndef __VGA__
#define __VGA__

#include "../address-map.h"

volatile int * pixel_ctrl_ptr;
volatile int pixel_buffer_start;              // global variable
short int Buffer1[240][512];                  // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

void __init__();

void background(int color);

void draw(int* deltaP, int X, int Y);

void draw_char(int x, int y, char c);

void write(char s[]);

void mouse(int X, int Y);

void scroll();

void plot_pixel(int x, int y, short int color);

void swap_buffers_on_vsync();


#endif