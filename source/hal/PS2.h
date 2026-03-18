#ifndef __PS2__
#define __PS2__

volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;


void PS2_init();

void PS2_deinit();

char get_char();

char* get_line();

char keycode_decoder(int keycode);

#endif

