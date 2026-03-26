//Hardware level display helpers


#ifndef __VGA__
#define __VGA__

#include "../address-map.h"
#include "../Adafruit/gfxfont.h"

#define FONT FreeMono9pt7b                   // global font when not specified otherwise

int CURSOR_X;                                 // the values for the cursor baseline, the bottom left of the line
int CURSOR_Y;
int CURSOR_X_DEFAULT;
int CURSOR_Y_DEFAULT; 

volatile int * pixel_ctrl_ptr;
volatile int * pixel_buffer_start;              // global variable
short int Buffer1[240][512];                  // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];


void swap_buffers_on_vsync();

void wait_for_vsync();

void plot_pixel(int x, int y, short int color);

void background(short int color);

void VGA_init();

void draw_line(int x0, int y0, int x1, int y1, short int line_color);

void swap(int* a, int* b);

void draw(int* deltaP, int X, int Y); // not sure if i will use this rn


/* by default these functions keep track of where the curcor is. If you want to write to 
a different pixel, change CURSOR_X and CURSOR_Y variables before calling the function */
void draw_char(char c);
void write(const char *str);


// void mouse(int X, int Y);

// void scroll();


void draw_staff(int x, int y); // x, y is starting position
void draw_brace(int x, int y);
void draw_bar_line(int x_center, int y_center);
void draw_treble_clef(int x, int y);
void draw_time_signature(int x, int y);

void draw_toolbar();


void draw_whole_note(int x_center, int y_center);
void draw_note(int x_center, int y_center);
void draw_half_note(int x_center, int y_center);
void draw_quarter_note(int x_center, int y_center);
void draw_eighth_note(int x_center, int y_center);
void draw_sixteenth_note(int x_center, int y_center);
void draw_ledger_line(int x_center, int y_center);
void draw_flag(int x, int y);

#endif