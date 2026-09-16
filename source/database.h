#ifndef __DATABASE__
#define __DATABASE__

#include <stdbool.h>
#include <stdlib.h>

#include "tunes.h"


typedef struct Note {
  char note; // C, D, E, F, G, A, B
  int octave; // support 4 and 5 (middle c is C4)
  char duration;  // length of note e.g. w (whole), h (half), q (quarter), e (eighth), s (sixteenth)
  bool is_sharp;
  struct Note * next;
} Note;

// this is a node in the linked list
typedef struct Score {   
  char name[64];           
  struct Note* notes; // this will just hold all of the notes in order   
  struct Score* next;  
  int tempo;  
} Score;

// this is the linked list
typedef struct ScoreList {
    struct Score* head; // start of list of all of the scores 
} ScoreList;

// ScoreList is a Linked List with Score as the node

// adds new_note to the Score member notes
void add_note(Note * new_note, Score * scr);

//returns true if a score with name alreaady exists
bool exists(char* name);     

//returns a pointer to the score if it exists
Score* find(char* name); 

//adds a score with name to the list
Score* add(char* name);       

//deletes the score from the list
void delete(char* name);      

//returns the names of all the scores
char* get_scores();                  


#endif
