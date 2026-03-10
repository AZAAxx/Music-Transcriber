#include "terminal.h"
#include "database.h"
#include "GLOBALS.h"
#include "hal/VGA.h"

int terminal(){
    background(BLACK);

    while(1){
        write(">> ");
        char command[] = get_string();
        if(command == "new"){
            char* name = get_string();                      //PS: I have forgotten C and dont know how to use strings
            if(exists(name)) write("Name already exists.");
            struct Score* scr = add(name);
            score(scr);
        }
        if(command == "open"){
            char* name = get_string();                      //PS: I have forgotten C and dont know how to use strings
            if(!exists(name)) {
                write("This score doesn't exist");
                continue;
            }
            struct Score* scr = find(name);
            score(scr);

        }
        if(command == "delete"){
            char* name = get_string();                      //PS: I have forgotten C and dont know how to use strings
            if(!exists(name)) {
                write("This score doesn't exist");
                continue;
            }
            struct Score* scr = find(name);
            delete(scr);
        }
        if(command == "list"){
            char** list = get_scores();
            //print all the score names
        }
        if(command == "help"){
            //print a help menu explaining the commands
        }
    }
}


char* get_string(){
    int Enter = 0;
    char* command;
    while(Enter == 1){
        //get input from the keyboard
        //store char in command
        //Enter = 1 if enter is pressed
    }
}