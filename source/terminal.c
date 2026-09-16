#include "terminal.h"
#include "database.h"
#include "hal/PS2.h"
#include "hal/VGA.h"
#include <string.h>


int terminal(){
    VGA_init();
    PS2_init();
    background(BLACK);

    while(1){
        write(">> ", WHITE);
        char * line = get_line();
        char * command = get_string(&line);

        const char * str_new    = "new";
        const char * str_open   = "open";
        const char * str_delete = "delete";
        const char * str_list   = "list";
        const char * str_help   = "help";
        const char * str_clear  = "clear";


        if(strcmp(command, str_new) == 0){
            char* name = get_string(&line);
            if(exists(name)) {
                write("Name already exists.\n", WHITE);
                continue;
            }
            add(name);
            write("New score '", WHITE);
            write(name, WHITE);
            write("' added.\n", WHITE);
        }

        else if(strcmp(command, str_open) == 0){
            char* name = get_string(&line);
            if(!exists(name)) {
                write("'", WHITE);
                write(name, WHITE);
                write("' doesn't exist.\n", WHITE);
                continue;
            }
            struct Score* scr = find(name);
            write("Opening '", WHITE);
            write(name, WHITE);
            write("'...\n", WHITE);
            CURSOR_X = CURSOR_X_DEFAULT;
            CURSOR_Y = CURSOR_Y_DEFAULT;
            score(scr);
        }

        else if(strcmp(command, str_delete) == 0){
            char* name = get_string(&line);
            if(!exists(name)) {
                write("'", WHITE);
                write(name, WHITE);
                write("' doesn't exist.\n", WHITE);
                continue;
            }
            delete(name);
            write("'", WHITE);
            write(name, WHITE);
            write("' deleted.\n", WHITE);
        }

        else if(strcmp(command, str_list) == 0){
            char* list = get_scores();
            write(list, WHITE);
        }

        else if(strcmp(command, str_help) == 0){
            write(help_menu, WHITE);
        }

        else if(strcmp(command, str_clear) == 0){
            background(BLACK);
            swap_buffers_on_vsync();
            pixel_buffer_start = *(pixel_ctrl_ptr + 1);
            background(BLACK);
            CURSOR_X = CURSOR_X_DEFAULT;
            CURSOR_Y = CURSOR_Y_DEFAULT;
        }

        else{
            write("Invalid command.\n", WHITE);
        }

    }
}

