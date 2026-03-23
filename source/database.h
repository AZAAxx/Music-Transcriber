#include "GLOBALS.h"

int exists(char* name);              //returns 1 if a score with name alreaady exists

Score* find(char* name);      //returns a pointer to the score if it exists

void add(char* name);       //adds a score with name to the list

void delete(char* name);       //deletes the score from the list

char* get_scores();                  //returns the names of all the scores
