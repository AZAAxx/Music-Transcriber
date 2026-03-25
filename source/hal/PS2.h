#ifndef __PS2__
#define __PS2__

#include <stdbool.h>

volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;

bool break_code;  // true if F0 seen
bool extended;     // true if E0 seen
bool shift;        // true if shift is currently pressed


void PS2_init();

void PS2_deinit();

char get_char();

char* get_line();

char keycode_decoder(int keycode);

#endif

