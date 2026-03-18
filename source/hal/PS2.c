#include "PS2.h"
#include "../address-map.h"
#include<string.h>

void PS2_init(){
    ps2_data_reg = (volatile int *) PS2_BASE;
    ps2_ctr_reg = (volatile int *) PS2_BASE + 1;

    *ps2_data_reg = 0xFF;   // reset and clear FIFO
}


char keycode_decoder(int keycode){

}



char get_keycode(){
    int RVALID, PS2_data;
    while(RVALID == 0){
        PS2_data = *(ps2_data_reg) & 0xFF;   // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000;          // extract the RVALID field
    }
    *ps2_data_reg = 0xFF;                    // reset and clear FIFO
    return PS2_data;
}

char* get_line(){
    char * command = "";
    while(1){
        int keycode = get_char();                 // get char from PS2 input
        if(keycode == 0x5A){                      // ENter has been pressed
            return command;
            ///write a newline
        }
        if(1 /*add bounds for allowed chars*/){
            char c = keycode_decoder(keycode);      // decode the keycode
            command = strcat(command, (char*){c, '\0'});   //store char in command
            // display the char on terminal
        }
    }
}
