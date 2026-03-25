#include "terminal.h"
#include "database.h"
#include "GLOBALS.h"
#include "hal/VGA.h"

char* help_menu = "\'new <name>\' -- create a new score\n\'open <name>\' -- open the specified score\n\'delete <name>\' -- open the specified score\n\'list\' -- list all scores";





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

        else if(command == "open"){
            char* name = get_string();                      //PS: I have forgotten C and dont know how to use strings
            if(!exists(name)) {
                write("This score doesn't exist");
                continue;
            }
            struct Score* scr = find(name);
            score(scr);
        }

        else if(command == "delete"){
            char* name = get_string();                      //PS: I have forgotten C and dont know how to use strings
            if(!exists(name)) {
                write("This score doesn't exist");
                continue;
            }
            struct Score* scr = find(name);
            delete(scr);
        }
        
        else if(command == "list"){
            char* list = get_scores();
            write(list);
        }

        else if(command == "help"){
            write(help_menu);
        }

        else{
            write("Invalid command.");
        }

    }
}


