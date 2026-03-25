#include "terminal-testing.c"
#include <stdbool.h>

volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;

#define PS2_BASE	0xFF200100

bool break_code;   // true if F0 seen
bool extended;     // true if E0 seen
bool shift;        // true if shift is currently pressed


void PS2_init(){
    ps2_data_reg = (volatile int *) PS2_BASE;
    ps2_ctr_reg = (volatile int *) PS2_BASE + 1;

    *ps2_data_reg = 0xFF;   // reset and clear FIFO
    *ps2_ctr_reg  = 0x1;    // enable the PS/2 port (RE bit)

    break_code = false; 
    extended = false;  
    shift = false;       
}


char keycode2ascii(int keycode, bool shift){
    switch (keycode) {
        case 0x1C: return shift ? 'A' : 'a';
        case 0x32: return shift ? 'B' : 'b';
        case 0x21: return shift ? 'C' : 'c';
        case 0x23: return shift ? 'D' : 'd';
        case 0x24: return shift ? 'E' : 'e';
        case 0x2B: return shift ? 'F' : 'f';
        case 0x34: return shift ? 'G' : 'g';
        case 0x33: return shift ? 'H' : 'h';
        case 0x43: return shift ? 'I' : 'i';
        case 0x3B: return shift ? 'J' : 'j';
        case 0x42: return shift ? 'K' : 'k';
        case 0x4B: return shift ? 'L' : 'l';
        case 0x3A: return shift ? 'M' : 'm';
        case 0x31: return shift ? 'N' : 'n';
        case 0x44: return shift ? 'O' : 'o';
        case 0x4D: return shift ? 'P' : 'p';
        case 0x15: return shift ? 'Q' : 'q';
        case 0x2D: return shift ? 'R' : 'r';
        case 0x1B: return shift ? 'S' : 's';
        case 0x2C: return shift ? 'T' : 't';
        case 0x3C: return shift ? 'U' : 'u';
        case 0x2A: return shift ? 'V' : 'v';
        case 0x1D: return shift ? 'W' : 'w';
        case 0x22: return shift ? 'X' : 'x';
        case 0x35: return shift ? 'Y' : 'y';
        case 0x1A: return shift ? 'Z' : 'z';

        case 0x45: return shift ? ')' : '0';
        case 0x16: return shift ? '!' : '1';
        case 0x1E: return shift ? '@' : '2';
        case 0x26: return shift ? '#' : '3';
        case 0x25: return shift ? '$' : '4';
        case 0x2E: return shift ? '%' : '5';
        case 0x36: return shift ? '^' : '6';
        case 0x3D: return shift ? '&' : '7';
        case 0x3E: return shift ? '*' : '8';
        case 0x46: return shift ? '(' : '9';

        case 0x29: return ' ';  // Space
        case 0x5A: return '\n'; // Enter

        default: return 0;
    }
}


char ps2_decoder(int keycode){

    // handle the break and extended codes
    if(keycode == 0xF0) {
        break_code = true;
        return 0;
    }
    else if(keycode == 0xE0) {
        extended = true;
        return 0;
    }

    // change ps2.shift when SHIFT is pressed depending on the break_code
    if(keycode == 0x12 || keycode == 0x59){
        if(break_code) shift = false;
        else shift = true;
        break_code = false;
        extended = false;
        return 0;
    }

    // ignore the scancode during the key release
    if(break_code){
        break_code = false;
        extended = false;
        return 0;
    }

    break_code = false;
    extended = false;
    
    // right now no support for extended keys
    char c = keycode2ascii(keycode, shift);
    return c;   
}



char get_keycode(){
    int RVALID = 0, PS2_data;

    while(1){
        PS2_data = *(ps2_data_reg);          // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000;          // extract the RVALID field
        if(RVALID) 
            return (PS2_data & 0xFF);
    } 
}



char get_char(){
    int keycode = get_keycode();
    char c = ps2_decoder(keycode);
    return c;
}

/*int example_keycode_stream[] = {0x15, 0xF0, 0x15,
                                0x1D, 0xF0, 0x1D,
                                0x25, 0xF0, 0x25,
                                0x2D, 0xF0, 0x2D
};

int main(){
    PS2_init();
    VGA_init();

    for(int i=0; i<12; i++){
        int keycode = example_keycode_stream[i];
        char c = ps2_decoder(keycode);
        //char c = get_char();
        draw_char(c);
    }   
    swap_buffers_on_vsync();
}*/


int main(){
    PS2_init();
	VGA_init();
    char c = get_char();
	//char c = 'h';
    draw_char(c);
    swap_buffers_on_vsync();
}