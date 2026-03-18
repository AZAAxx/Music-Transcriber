//define global variables such as FPS, certain color codes, certain important pixels etc. 

#ifndef __GLOBALS__
#define __GLOBALS__

struct Note {   
  char note;          
  int octave;
  int duration;
  int time;
};

struct Score {   
  char* name;           
  struct Note** notes;       
};

struct ScoreList {
    struct Score** list;
};




const int BLACK = 0x00000000;
const int WHITE = 0xFFFFFFFF;

int* whole_note;         //each int* below should be a list of delta_x, delta_y values from a center that will be colored 
int* half_note;
int* quarter_note;
int* eighth_note;
int* sixteenth_note;

int* toolbar;
int* staff;
int* barline;

int* treble_cleff;
int* bass_cleff;


#endif




