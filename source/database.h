#ifndef __DATABASE__
#define __DATABASE__

#include "GLOBALS.h"

int exists(char* name);              //returns 1 if a score with name alreaady exists

struct Score* add(char* name);       //adds a score with name to the list

void delete(struct Score* scr);       //deletes the score from the list

struct Score* find(char* name);      //returns a pointer to the score if it exists

char* get_scores();                  //returns the names of all the scores


#endif
