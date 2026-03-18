#include "terminal-testing.c"


volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;

#define PS2_BASE	0xFF200100
#define JTAG_UART_BASE			0xFF201000


void PS2_init(){
    ps2_data_reg = (volatile int *) PS2_BASE;
    ps2_ctr_reg = (volatile int *) PS2_BASE + 1;

    *ps2_data_reg = 0xFF;   // reset and clear FIFO
}


char get_char(){
    int RVALID = 0, PS2_data;
    while(RVALID == 0){
        PS2_data = *(ps2_data_reg) & 0xFF;   // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000;          // extract the RVALID field
    }
    *ps2_data_reg = 0xFF;                    // reset and clear FIFO
    return PS2_data;
}


void putc(char c) {
    volatile int * jtag_uart_ptr = (int *) JTAG_UART_BASE;
    
    // Wait for the JTAG UART to be ready (check WSPACE)
    while ((*jtag_uart_ptr & 0xFFFF0000) == 0);
    
    // Write the character
    *jtag_uart_ptr = c;
}

int main(){
    PS2_init();
    char c = get_char();
    draw_char(&FONT, c);
    swap_buffers_on_vsync();
}