#ifndef __PS2__
#define __PS2__

#include <stdbool.h>

volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;

bool break_code;  // true if F0 seen
bool extended;     // true if E0 seen
bool shift;        // true if shift is currently pressed

// initializes the PS2 interface
void PS2_init();

// returns the character corresponding to a keycode
char keycode2ascii(int keycode, bool shift);

// processes the audio to manage the sequence of keycodes, like support for SHIFT
char ps2_decoder(int keycode);

// gets the keycode from the keyboard
int get_keycode();


// USE THIS: puts the above methods together to get a character from keyboard
char get_char();

// USE THIS: gets a line from the user, terminated by \n. Simultaneously draws the line.
char * get_line();

// USE THIS: gets the first string seperated by ' ' characters from a line terminated by \n 
char * get_string(char ** line);  

#endif

