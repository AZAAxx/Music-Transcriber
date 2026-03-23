#include "source/GLOBALS.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ScoreList is a Linked List with Score as the node
ScoreList scoreList = {NULL};

int exists(char* name) {             // returns 1 if a score with name already exists, 0 if not exists
    // search through the linked list and check for the score name
    int exist = 0;
    Score* current = scoreList.head;
    while (current != NULL) { 
        if (strcmp(current->name, name) == 0) { // returns 0 if strings are identical
            exist = 1;
        }
        current = current->next;
    }
    return exist;
}

Score* find(char* name) {      // returns a pointer to the score if it exists
    // search through the whole list, check the names
    Score* found = NULL;
    // doesn't exist
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

void add(char* name) {       // adds a score with name to the list
    // put newest score at the very end
    Score* current = scoreList.head;
    Score* prev = NULL;
    while (current != NULL) {
        prev = current;
        current = current->next;
    }

    Score* new_score = malloc(sizeof(Score));
    strcpy(new_score->name, name);
    new_score->next = NULL;

    if (prev == NULL) scoreList.head = new_score;
    if (prev != NULL) prev->next = new_score;
}

void delete(char* name) {       // deletes the score from the list
    // delete the score with the name specified
    Score* current = scoreList.head;
    Score* prev = NULL;
    // doesn't exist
    if (exists(name) == 0) return;

    // exists
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // last score in multi-score list
            if (prev == NULL) {
                scoreList.head = current->next; // removing the head
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current-> next;
    }

    return;
}

char* get_scores() {                  // returns the names of all the scores
    // go through each score return names of all scores
    Score* current = scoreList.head;
    // empty aka no scores in list
    if (current == NULL) return NULL;

    char* all_names = malloc(1024);
    all_names[0] = '\0';

    // not empty list
    while (current != NULL) {
        strcat(all_names, current->name); // adds the name of the current score to the string
        strcat(all_names, "    "); // for the space between the scores (4 spaces)
        current = current->next;
    }
    return all_names;
}