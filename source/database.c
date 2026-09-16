#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



void add_note(Note * new_note, Score * scr){
    Note * last_note = scr->notes;
    if (last_note->note == '\0') {
        scr->notes = new_note;
        free(last_note); // free old sentinel
        return;
    }

    // go to last real note
    while (last_note->next != NULL && last_note->next->note != '\0') {
        last_note = last_note->next;
    }
    if (last_note->next != NULL && last_note->next->note == '\0') {
        free(last_note->next);
        last_note->next = NULL;
    }

    last_note->next = new_note;
}


bool exists(char* name) {             // returns 1 if a score with name already exists, 0 if not exists
    bool exist = false;
    Score* current = scoreList.head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            exist = true;
        }
        current = current->next;
    }
    return exist;
}

Score* find(char* name) {      // returns a pointer to the score if it exists
    Score* found = NULL;
    if (exists(name) == 0) return found;

    Score* current = scoreList.head;
    while(current != NULL) {
        if ((strcmp(current->name, name) == 0)) {
            found = current;
            break;
        }
        current = current->next;
    }

    return found;
}

Score* add(char* name) {       // adds a score with name to the list
    Score* current = scoreList.head;
    Score* prev = NULL;
    while (current != NULL) {
        prev = current;
        current = current->next;
    }

    Score* new_score = malloc(sizeof(Score));
    strcpy(new_score->name, name);
    new_score->next = NULL;
    new_score->tempo = 120;    // arbitrary default value

    Note* sentinel = malloc(sizeof(Note));
    sentinel->note = '\0';
    sentinel->octave = 0;
    sentinel->duration = '\0';
    sentinel->next = NULL;
    new_score->notes = sentinel;

    if (prev == NULL) scoreList.head = new_score;
    if (prev != NULL) prev->next = new_score;

    score_count++;
    return new_score;
}

void delete(char* name) {       // deletes the score from the list
    Score* current = scoreList.head;
    Score* prev = NULL;
    if (exists(name) == 0) return;

    score_count--;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                scoreList.head = current->next;
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

char* get_scores() {                  // returns the names of all the scores
    Score* current = scoreList.head;
    if (current == NULL) return NULL;

    int count = 0;
    Score* tmp = scoreList.head;
    while (tmp != NULL) { count++; tmp = tmp->next; }

    char* all_names = malloc(count * 100 * sizeof(char));
    all_names[0] = '\0';

    while (current != NULL) {
        strcat(all_names, current->name);
        strcat(all_names, "\n");
        current = current->next;
    }
    return all_names;
}