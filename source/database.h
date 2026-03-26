#ifndef __DATABASE__
#define __DATABASE__

#include "GLOBALS.h"
#include <stdbool.h>

//returns true if a score with name alreaady exists
bool exists(char* name);     

//returns a pointer to the score if it exists
struct Score* find(char* name); 

//adds a score with name to the list
Score* add(char* name);       

//deletes the score from the list
void delete(char* name);      

//returns the names of all the scores
char* get_scores();                  


#endif
