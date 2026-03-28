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

// swaps the front and back buffers, does NOT update the pixel_buffer_start variable
void swap_buffers_on_vsync();

// writes color to (x, y) on the VGA
void plot_pixel(int x, int y, short int color);

// writes the color to the whole screen
void background(short int color);

// initializes the VGA, sets up the buffers, pointers, and values
void VGA_init();



/* Functions used for terminal.c */

// draws a character at (CURSOR_X, CURSOR_Y). NEVER use in terminal.c because it doesn't update the cursor
void draw_char(char c, short int color);

// USE THIS: writes a string at (CURSOR_X, CURSOR_Y), updates the cursor position
void write(const char *str);

// deletes the last character c
void delete(char c);


/* Functions used for score.c */

// draws a line between (x0, y0) and (x1, y1), with color line_color
void draw_line(int x0, int y0, int x1, int y1, short int line_color);

// swaps a and b
void swap(int* a, int* b);

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





const int NOTE_WIDTH = 7; // this many pixels

const short int WHITE = 0xFFFF;
const short int BLACK = 0x0000;
const short int TOOLBAR_COLOR = 0x731F; // this is light purple right now

const int VERT_MIN = 0;
const int VERT_MAX = 239; 
const int HOR_MIN = 0;
const int HOR_MAX = 319; 

int current_hor;
int current_vert;

volatile unsigned int *SW = (unsigned int*)SW_BASE;

int staff_center; // set to middle of staff to calculate stem direction
char note_type; // 'w' whole, 'h' half, 'q' quarter, 'e' eighth, 's' sixteenth

int* whole_note;         //each int* below should be a list of delta_x, delta_y values from a center that will be colored 
int* half_note;
int* quarter_note;
int* eighth_note;
int* sixteenth_note;

int* toolbar;
int* staff;
int* barline;

int* treble_cleff;
int* bass_cleff;

int brace[36][5] = {
    {0,0,0,1,1},
    {0,0,1,1,0},
    {0,1,1,0,0},
    {1,1,0,0,0},
    {1,0,0,0,0},
    {1,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
    {0,0,1,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,1,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {1,1,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {0,1,0,0,0},
    {0,1,1,0,0},
    {0,0,1,1,0},
    {0,0,0,1,1}
};

int treble_clef[44][16] = { // center around G better
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0},
    {0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
};

int time_sig_4_4[36][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,1,1,1,1}, // line 18
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,1,1,1,1}
};

int whole_note[9][15] = {
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,1,1,1,1,0,0},
    {0,1,1,1,0,0,0,0,0,0,1,1,1,1,0},
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1}, // center line
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
    {0,1,1,1,1,0,0,0,0,0,0,1,1,1,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}
};

int note[9][15] = {
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // center line
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}
};

int flag_up[12][8] = {
    {1,1,1,1,0,0,0,0},
    {1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1}
};

int flag_down[12][15] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},    
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}
};

int sharp[12][8] = {
    {0,0,1,0,0,1,0,0},
    {0,0,1,0,0,1,1,1},
    {0,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,0},
    {1,1,1,0,0,1,0,0},
    {0,0,1,0,0,1,0,0},
    {0,0,1,0,0,1,0,0},
    {0,0,1,0,0,1,1,1},
    {0,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,0},
    {1,1,1,0,0,1,0,0},
    {0,0,1,0,0,1,0,0}
};

int flat[12][8] = {
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,1,1,1,0},
    {1,0,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1},
    {1,1,0,0,0,0,1,1},
    {1,0,0,0,0,1,1,0},
    {1,0,0,0,1,1,0,0},
    {1,1,1,1,0,0,0,0}
};

#endif