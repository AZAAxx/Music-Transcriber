#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Note {   
    char note; // C, D, E, F, G, A, B         
    int octave; // only support 4 and 5 right now (middle c ic C4)
    char duration;  // length of note e.g. w (whole), h (half), q (quarter), e (eighth), s (sixteenth)
} Note;
  
// this is a node in the linked list
typedef struct Score {   
    char name[64];           
    struct Note notes[64]; // this will just hold all of the notes in order   
    struct Score* next;    
} Score;
  
// this is the linked list
typedef struct ScoreList {
    struct Score* head; // start of list of all of the scores 
} ScoreList;

// ScoreList is a Linked List with Score as the node
ScoreList scoreList = {NULL};
int score_count;

int exists(char* name);              //returns 1 if a score with name alreaady exists
Score* add(char* name);       //adds a score with name to the list
void delete(char* name);       //deletes the score from the list
struct Score* find(char* name);      //returns a pointer to the score if it exists
char* get_scores();                  //returns the names of all the scores

int main() {
    // test exists with nothing in list
    printf("--- Empty list ---\n");
    printf("twinkle exists? %d\node to joy exists? %d\nmary exists? %d\n",
        exists("twinkle"), exists("ode to joy"), exists("mary had a little lamb"));
 
    // test find on empty list
    Score* found = find("twinkle");
    if (found == NULL) printf("twinkle: not found\n");
    else printf("twinkle: found\n");
 
    // test delete on empty list (should do nothing)
    delete("twinkle");
    printf("Scores: %s\n", get_scores());
 
    // add one score, then delete it
    printf("\n--- Add twinkle, then delete it ---\n");
    add("twinkle");
    printf("twinkle exists? %d\n", exists("twinkle"));
 
    found = find("twinkle");
    if (found == NULL) printf("twinkle: not found\n");
    else printf("twinkle: found\n");
 
    delete("twinkle");
    printf("Scores: %s\n", get_scores());
 
    // add three scores, delete two
    printf("\n--- Add three scores ---\n");
    add("twinkle");
    add("ode to joy");
    add("mary had a little lamb");
 
    printf("twinkle exists? %d\node to joy exists? %d\nmary exists? %d\n",
        exists("twinkle"), exists("ode to joy"), exists("mary had a little lamb"));
 
    found = find("twinkle");
    if (found == NULL) printf("twinkle: not found\n");
    else printf("twinkle: found\n");
 
    delete("ode to joy");
    printf("After deleting 'ode to joy' — Scores: %s\n", get_scores());
 
    delete("mary had a little lamb");
    printf("After deleting 'mary' — Scores: %s\n", get_scores());
 
    return 0;
}

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

Score* add(char* name) {       // adds a score with name to the list
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

    score_count++;
    return new_score;
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

    score_count--;
    return;
}

char* get_scores() {                  // returns the names of all the scores
    // go through each score return names of all scores
    Score* current = scoreList.head;
    // empty aka no scores in list
    if (current == NULL) return NULL;

    char* all_names = malloc(score_count*100 * sizeof(char));
    all_names[0] = '\0';

    // not empty list
    while (current != NULL) {
        strcat(all_names, current->name); // adds the name of the current score to the string
        strcat(all_names, "    "); // for the space between the scores (4 spaces)
        current = current->next;
    }
    return all_names;
}