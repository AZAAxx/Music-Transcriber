#ifndef __DATABASE__
#define __DATABASE__

#include "GLOBALS.h"
#include <stdbool.h>

bool exists(char* name);       //returns true if a score with name alreaady exists

Score* add(char* name);       //adds a score with name to the list

void delete(char* name);       //deletes the score from the list

struct Score* find(char* name);      //returns a pointer to the score if it exists

char* get_scores();                  //returns the names of all the scores


#endif
