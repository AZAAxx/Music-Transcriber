#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



void add_note(Note * new_note, Score * scr){
    Note * last_note = scr->notes;
    if (last_note->note == '\0') {                         // if notes list is empty, set new_note as the first note 
        scr->notes = new_note;
        free(last_note);                                   // free old sentinel
        return;
    }
    
    while (last_note->next != NULL && last_note->next->note != '\0') { // go to last real note
        last_note = last_note->next;
    }
    if (last_note->next != NULL && last_note->next->note == '\0') {    // if the last score is empty
        free(last_note->next);                             // remove (replace) the score
        last_note->next = NULL;
    }

    last_note->next = new_note;                            // append new_note to the end of the list
}


bool exists(char* name) {                                  // returns 1 if a score with name already exists, 0 if not exists
    bool exist = false;
    Score* current = scoreList.head;
    while (current != NULL) {                              // go through all the scores in the list and compare names
        if (strcmp(current->name, name) == 0) {            // return true if found  
            exist = true;
        }
        current = current->next;
    }
    return exist;
}

Score* find(char* name) {                                 // returns a pointer to the score if it exists
    Score* found = NULL;
    if (exists(name) == 0) return found;                  // return if Score with 'name' does not exist

    Score* current = scoreList.head;
    while(current != NULL) {                               // go through all the Scores in the list and compare names
        if ((strcmp(current->name, name) == 0)) {          // when name found, return the Score *
            found = current; 
            break;
        }
        current = current->next;
    }
    return found;
}

Score* add(char* name) {                                   // adds a score with name to the list
    Score* current = scoreList.head;
    Score* prev = NULL;
    while (current != NULL) {                              // go to the last Score
        prev = current;
        current = current->next;
    }

    Score* new_score = malloc(sizeof(Score));              // allocate a new Score and assign initial/default values
    strcpy(new_score->name, name);
    new_score->next = NULL;
    new_score->tempo = 120;                                // arbitrary default value

    Note* sentinel = malloc(sizeof(Note));                 // allocate a new note with default values as a stand-in
    sentinel->note = '\0';
    sentinel->octave = 0;
    sentinel->duration = '\0';
    sentinel->next = NULL;
    new_score->notes = sentinel;

    if (prev == NULL) scoreList.head = new_score;          // if ScoreList is empty, assign new_score as its head
    if (prev != NULL) prev->next = new_score;              // else, append new_score to the last score

    score_count++;
    return new_score;
}

void delete(char* name) {                                  // deletes the score from the list
    Score* current = scoreList.head;
    Score* prev = NULL;
    if (exists(name) == 0) return;                         // return if the Score doesn't exist

    score_count--;
    while (current != NULL) {                              // go through all the scores
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                scoreList.head = current->next;            // if score is the head, assign the next score as the head
            } else {
                prev->next = current->next;  
            }
            free(current); 
            return;
        }
        prev = current;
        current = current->next;
    }

    return;
}

char* get_scores() {                                       // returns the names of all the scores
    Score* current = scoreList.head;
    if (current == NULL) return NULL;                      // return NULL of there are no scores

    int count = 0;
    Score* tmp = scoreList.head;
    while (tmp != NULL) { count++; tmp = tmp->next; }      // count number of scores for memory allocation

    char* all_names = malloc(count * 100 * sizeof(char));  // allocate memory for the list
    all_names[0] = '\0';

    while (current != NULL) {                              // build the list of names with newlines in between for printing
        strcat(all_names, current->name);
        strcat(all_names, "\n");
        current = current->next;
    }
    return all_names;
}