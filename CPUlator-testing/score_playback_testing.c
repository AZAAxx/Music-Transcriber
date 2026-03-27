#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct Note {   
  char note; // C, D, E, F, G, A, B         
  int octave; // only support 4 and 5 right now (middle c ic C4)
  char duration;  // length of note e.g. w (whole), h (half), q (quarter), e (eighth), s (sixteenth)
} Note;

typedef struct Score {   
  char name[64];           
  struct Note notes[64];
  struct Score* next;    
} Score;

typedef struct ScoreList {
    struct Score* head;
} ScoreList;

#define LED_BASE		0xFF200000
#define LEDR_BASE		0xFF200000
#define HEX3_HEX0_BASE		0xFF200020
#define HEX5_HEX4_BASE		0xFF200030
#define SW_BASE			0xFF200040
#define KEY_BASE		(volatile int *) 0xFF200050
#define JP1_BASE		0xFF200060
#define JP2_BASE		0xFF200070
#define PS2_BASE		0xFF200100
#define PS2_DUAL_BASE		0xFF200108
#define JTAG_UART_BASE		0xFF201000
#define IrDA_BASE		0xFF201020
#define TIMER_BASE		0xFF202000
#define TIMER_2_BASE		0xFF202020
#define AV_CONFIG_BASE		0xFF203000
#define RGB_RESAMPLER_BASE	0xFF203010
#define PIXEL_BUF_CTRL_BASE	0xFF203020
#define CHAR_BUF_CTRL_BASE	0xFF203030
#define AUDIO_BASE		(volatile int *)0xFF203040
#define VIDEO_IN_BASE		0xFF203060
#define EDGE_DETECT_CTRL_BASE	0xFF203070
#define ADC_BASE		0xFF204000

#define T_SAMPLE 125e-6
#define FREQ_SAMPLE 8000

volatile int * pixel_ctrl_ptr;

volatile int pixel_buffer_start;

short int Buffer1[240][512];
short int Buffer2[240][512];

const int NOTE_WIDTH = 7;

const short int WHITE = 0xFFFF;
const short int BLACK = 0x0000;
const short int TOOLBAR_COLOR = 0x731F;

const int VERT_MIN = 0;
const int VERT_MAX = 239; 
const int HOR_MIN = 0;
const int HOR_MAX = 319; 

int current_hor;
int current_vert;

volatile unsigned int *SW = (unsigned int*)SW_BASE;

int staff_center;
char note_type;
bool note_drawn = false;

int brace[36][5] = {
    {0,0,0,1,1},
    {0,0,1,1,0},
    {0,1,1,0,0},
    {1,1,0,0,0},
    {1,0,0,0,0},
    {1,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
    {0,0,1,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,1,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {1,1,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {0,1,0,0,0},
    {0,1,1,0,0},
    {0,0,1,1,0},
    {0,0,0,1,1}
};

int treble_clef[44][16] = {
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0},
    {0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
};

int time_sig_4_4[36][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,1,1,1,1}
};

int whole_note[9][15] = {
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,1,1,1,1,0,0},
    {0,1,1,1,0,0,0,0,0,0,1,1,1,1,0},
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
    {0,1,1,1,1,0,0,0,0,0,0,1,1,1,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}
};

int note[9][15] = {
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}
};

int flag_up[12][8] = {
    {1,1,1,1,0,0,0,0},
    {1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1}
};

int flag_down[12][15] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},    
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}
};

Score* score_test = &(Score){
    .name = "twinkle",
    .next = NULL,
    .notes = {
        {'C', 4, 'q'},   
        {'C', 4, 'q'},   
        {'G', 4, 'q'},   
        {'G', 4, 'q'},   
        {'A', 4, 'q'},   
        {'A', 4, 'q'},   
        {'G', 4, 'h'},
		{'F', 4, 'q'},
		{'F', 4, 'q'},
		{'E', 4, 'q'},
		{'E', 4, 'q'},
		{'D', 4, 'q'},
		{'D', 4, 'q'},
		{'C', 4, 'h'},
		{'C', 4, 'q'},
		{'D', 4, 'q'},
		{'E', 4, 'q'},
		{'F', 4, 'q'},
		{'G', 4, 'q'},
		{'A', 4, 'q'},
		{'B', 4, 'q'},
		{'C', 5, 'q'},
        {'\0', 0, '\0'}
    }
};

void draw_score(Score* score);
void play_score(Score* score);

void AUDIO_init();
int isFIFOavailable();
void play_frequency(double frequency, double volume, double duration);

void swap_buffers_on_vsync();
void wait_for_vsync();
void plot_pixel(int x, int y, short int color);
void background(short int color);
void VGA_init();
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);

void draw_staff(int x, int y);
void draw_brace(int x, int y);
void draw_bar_line(int x_center, int y_center);
void draw_treble_clef(int x, int y);
void draw_time_signature(int x, int y);
void draw_toolbar();
void draw_whole_note(int x_center, int y_center);
void draw_note(int x_center, int y_center);
void draw_half_note(int x_center, int y_center);
void draw_quarter_note(int x_center, int y_center);
void draw_eighth_note(int x_center, int y_center);
void draw_sixteenth_note(int x_center, int y_center);
void draw_ledger_line(int x_center, int y_center);
void draw_flag(int x, int y);

int main() {
    AUDIO_init();

    pixel_ctrl_ptr = (volatile int *)0xFF203020;

    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;
    swap_buffers_on_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    background(WHITE);

    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); 
    background(WHITE);
	
    draw_staff(15, 30);
    draw_time_signature(32, 30);
    // draw_toolbar();
	draw_staff(15, 110);
	draw_staff(15, 190);
	draw_bar_line(HOR_MAX - 15 - 2, 190);
	draw_bar_line(HOR_MAX - 15 - 4, 190);
	
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); 

    int edge_cap;
	
    current_hor = 60;
    current_vert = 30 + 27;
    staff_center = 30 + 18;
	
    while (1) {
        unsigned int sw = *SW & 0x3FF;
		
        if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3);
            if (edge_cap & 0x1) {
                draw_score(score_test);
            }
            if (edge_cap & 0x2) {
                play_score(score_test);
            }
        }
		*(KEY_BASE + 3) = 0x3FF;
    }
}

void draw_score(Score* score){
	// handles drawing the whole score on the page
    // draws the score using different functions for drawing notes
    // draw each note here and call it once in the main function
    for (int note_idx = 0; note_idx < 64; note_idx++) { // note_idx for note array
        // read the duration here instead of edge_cap
		Note* current_note = &score->notes[note_idx];
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
		
        if (pitch == '\0') break;

        note_drawn = true;
        if      (duration == 'w') note_type = 'w';
        else if (duration == 'h') note_type = 'h';
        else if (duration == 'q') note_type = 'q';
        else if (duration == 'e') note_type = 'e';
        else if (duration == 's') note_type = 's';
		
        // check if going off screen
        if      (duration == 'w') {
            if ((current_hor + 120) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 'h') {
            if ((current_hor + 60) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 'q') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 'e') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }
        else if (duration == 's') {
            if ((current_hor + 30) > (HOR_MAX - 15)) {
                current_hor = 60;
                current_vert += (80);
				staff_center += (80);
            }
        }

		// read note here (note and octave together)
        if      ((pitch == 'C') && (octave == 4)) current_vert = staff_center + 27;
        // idea for accidentals put accidental as member of Note struct
        // read if sharp or flat and draw those --> need graphics for this
		else if ((pitch == 'D') && (octave == 4)) current_vert = staff_center + 23;
        else if ((pitch == 'E') && (octave == 4)) current_vert = staff_center + 18;
        else if ((pitch == 'F') && (octave == 4)) current_vert = staff_center + 13;
        else if ((pitch == 'G') && (octave == 4)) current_vert = staff_center + 9;
        else if ((pitch == 'A') && (octave == 4)) current_vert = staff_center + 5;
        else if ((pitch == 'B') && (octave == 4)) current_vert = staff_center;
        else if ((pitch == 'C') && (octave == 5)) current_vert = staff_center - 5;
        else if ((pitch == 'D') && (octave == 5)) current_vert = staff_center - 9;
        else if ((pitch == 'E') && (octave == 5)) current_vert = staff_center - 14;
        else if ((pitch == 'F') && (octave == 5)) current_vert = staff_center - 18;
        else if ((pitch == 'G') && (octave == 5)) current_vert = staff_center - 23;
        else if ((pitch == 'A') && (octave == 5)) current_vert = staff_center - 27;
        else if ((pitch == 'B') && (octave == 5)) current_vert = staff_center - 32;
        else if ((pitch == 'C') && (octave == 6)) current_vert = staff_center - 36;
		// end checking note and octave
		
		// keep this
        draw_staff(15, 30);
        draw_time_signature(32, 30);
        // draw_toolbar();
		draw_staff(15, 110);
		draw_staff(15, 190);
		draw_bar_line(HOR_MAX - 15 - 2, 190);
		draw_bar_line(HOR_MAX - 15 - 4, 190);
		
		// keep note_drawn thing
    	// add more notes to this
        if (note_drawn) {
			// add ledger line function for anything that needs it
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23))
                draw_ledger_line(current_hor, current_vert);
            // end ledger line block
			
			// read note duration here again from note_type which is set from duration
			if      (note_type == 'w') draw_whole_note(current_hor, current_vert);
            else if (note_type == 'h') draw_half_note(current_hor, current_vert);
            else if (note_type == 'q') draw_quarter_note(current_hor, current_vert);
            else if (note_type == 'e') draw_eighth_note(current_hor, current_vert);
            else if (note_type == 's') draw_sixteenth_note(current_hor, current_vert);
        }
		// end of note drawing block
		
		// keep this
        swap_buffers_on_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); 

		// this should be the same as the other if statement with (note_drawn) except with incrementing current values
        if (note_drawn) {
            if ((current_vert < staff_center - 23) || (current_vert > staff_center + 23))
                draw_ledger_line(current_hor, current_vert);
            if (note_type == 'w') {
                draw_whole_note(current_hor, current_vert);
                current_hor += 120;
            }
            else if (note_type == 'h') {
                draw_half_note(current_hor, current_vert);
                current_hor += 60;
            }
            else if (note_type == 'q') {
                draw_quarter_note(current_hor, current_vert);
                current_hor += 30;
            }
            else if (note_type == 'e') {
                draw_eighth_note(current_hor, current_vert);
                current_hor += 30;
            }
            else if (note_type == 's') {
                draw_sixteenth_note(current_hor, current_vert);
                current_hor += 30;
            }
            note_drawn = false;
        }
		// end of note drawing block
    }
}

void play_score(Score* score){
    for (int note_idx = 0; note_idx < 64; note_idx++) {
        Note* current_note = &score->notes[note_idx];
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
        double frequency = 0.0;
        double dur = 0.0;

        int bpm = 120;
        double secs_per_beat = 60.0 / ((double) bpm);
        
        if (pitch != '\0') {
            if      (duration == 'w') dur = secs_per_beat * 4;
            else if (duration == 'h') dur = secs_per_beat * 2;
            else if (duration == 'q') dur = secs_per_beat;
            else if (duration == 'e') dur = secs_per_beat / 2;
            else if (duration == 's') dur = secs_per_beat / 4;
			
            if      ((pitch == 'C') && (octave == 4)) frequency = 261.63;
            else if ((pitch == 'D') && (octave == 4)) frequency = 293.66;
            else if ((pitch == 'E') && (octave == 4)) frequency = 329.63;
            else if ((pitch == 'F') && (octave == 4)) frequency = 349.23;
            else if ((pitch == 'G') && (octave == 4)) frequency = 392.00;
            else if ((pitch == 'A') && (octave == 4)) frequency = 440.00;
            else if ((pitch == 'B') && (octave == 4)) frequency = 493.88;
            else if ((pitch == 'C') && (octave == 5)) frequency = 523.25;
            else if ((pitch == 'D') && (octave == 5)) frequency = 587.33;
            else if ((pitch == 'E') && (octave == 5)) frequency = 659.25;
            else if ((pitch == 'F') && (octave == 5)) frequency = 698.46;
            else if ((pitch == 'G') && (octave == 5)) frequency = 783.99;
            else if ((pitch == 'A') && (octave == 5)) frequency = 880.00;
            else if ((pitch == 'B') && (octave == 5)) frequency = 987.77;
            else if ((pitch == 'C') && (octave == 6)) frequency = 1046.50;

            double volume = 0x7FFFFF;
            play_frequency(frequency, volume, dur);
			play_frequency(0, volume, 0.1);
        }
    }
}

void AUDIO_init(){
    volatile int * audio_ptr = AUDIO_BASE;
    *(audio_ptr) = 0x8;   // set CW bit to clear/reset the FIFOs first
    *(audio_ptr) = 0x0;   // then clear it to normal operation
}

int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);
    //RAC = audio_counters & 0xFF;  
    int WSC = (audio_counters >> 16) & 0xFF;
    int RAC = audio_counters & 0xFF;
    
    if(WSC > 0 && RAC > 0) return 1;
    return 0;                           
}

void play_frequency(double frequency, double volume, double duration){
    double t_sample = 125.0 / 1000000.0;
    int half_period_samples = (int)((1.0 / frequency / 2.0) / t_sample);
    if (half_period_samples < 1) half_period_samples = 1;
    int total_samples = (int)(duration / t_sample);

    int counter = 0;
    int sign = 1;
    int samples_written = 0;

    while (samples_written < total_samples) {
        if (isFIFOavailable()) {
            *(AUDIO_BASE + 2) = (int)(sign * volume);
            *(AUDIO_BASE + 3) = (int)(sign * volume);
            counter++;
            samples_written++;
            if (counter >= half_period_samples) {
                sign = -sign;
                counter = 0;
            }
        }
    }
}

void wait_for_vsync() {
    swap_buffers_on_vsync();
}

// void swap_buffers_on_vsync() {
//     *pixel_ctrl_ptr = 1;
//     while (*(pixel_ctrl_ptr + 3) & 0x1);
// }

void swap_buffers_on_vsync() {
    pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;
    *pixel_ctrl_ptr = 1;                                // write 1 into the buffer reg to request a swap
    while (*(pixel_ctrl_ptr + 3) & 0x1);                // Wait until status.S turns 0
}

void plot_pixel(int x, int y, short int color) {
    volatile short int *one_pixel_address;
    one_pixel_address = (short int*)(pixel_buffer_start + (y << 10) + (x << 1));
    *one_pixel_address = color;
}

void background(short int color) {
    for (int x = 0; x < 320; x++)
        for (int y = 0; y < 240; y++)
            plot_pixel(x, y, color); 
}

void draw_line(int x0, int y0, int x1, int y1, short int color) {
    bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    if (is_steep) { swap(&x0, &y0); swap(&x1, &y1); }
    if (x0 > x1)  { swap(&x0, &x1); swap(&y0, &y1); }
	
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;
    int y_step = (y0 < y1) ? 1 : -1;
	
    for (int x = x0; x < x1; x++) {
        if (is_steep) plot_pixel(y, x, color);
        else          plot_pixel(x, y, color);
        error += deltay;
        if (error > 0) {
            y += y_step;
            error -= deltax;
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void VGA_init(){
    pixel_ctrl_ptr = (volatile int *) PIXEL_BUF_CTRL_BASE;
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;
    swap_buffers_on_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;           // FIX 3 (same — no cast)
    background(BLACK);
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);     // FIX 3 (same — no cast)
    background(BLACK);  
}

void draw_staff(int x, int y) { 
    draw_line(x, y,        HOR_MAX - x, y,        BLACK);
    draw_line(x, y + 9,    HOR_MAX - x, y + 9,    BLACK);
    draw_line(x, y + 18,   HOR_MAX - x, y + 18,   BLACK);
    draw_line(x, y + 27,   HOR_MAX - x, y + 27,   BLACK);
    draw_line(x, y + 36,   HOR_MAX - x, y + 36,   BLACK);
    draw_brace(x - 8, y);
    draw_treble_clef(x, y - 4);
    draw_bar_line(x, y);
    draw_bar_line(HOR_MAX - x - 1, y);
}

void draw_brace(int x, int y) {
    for (int i = 0; i < 36; i++)
        for (int j = 0; j < 5; j++)
            if (brace[i][j] == 1)
                plot_pixel(x + j, y + i, BLACK);
}

void draw_bar_line(int x_center, int y_center) {
    draw_line(x_center, y_center, x_center, y_center + 36, BLACK);
}

void draw_treble_clef(int x, int y) {
    for (int i = 0; i < 44; i++)
        for (int j = 0; j < 16; j++)
            if (treble_clef[i][j] == 1)
                plot_pixel(x + j, y + i, BLACK);
}

void draw_time_signature(int x, int y) {
    for (int i = 0; i < 36; i++)
        for (int j = 0; j < 8; j++)
            if (time_sig_4_4[i][j] == 1)
                plot_pixel(x + j, y + i, BLACK);
}

void draw_toolbar() {
    draw_line(103, 210, HOR_MAX - 103, 210, TOOLBAR_COLOR);
    draw_line(100, 211, HOR_MAX - 100, 211, TOOLBAR_COLOR);
    draw_line(100, 212, HOR_MAX - 100, 212, TOOLBAR_COLOR);
    draw_line(98,  213, HOR_MAX - 98,  213, TOOLBAR_COLOR);
    draw_line(97,  214, HOR_MAX - 97,  214, TOOLBAR_COLOR);
    draw_line(97,  215, HOR_MAX - 97,  215, TOOLBAR_COLOR);
    for (int i = 216; i < 225; i++)
        draw_line(96, i, HOR_MAX - 96, i, TOOLBAR_COLOR);
    draw_line(97,  225, HOR_MAX - 97,  225, TOOLBAR_COLOR);
    draw_line(97,  226, HOR_MAX - 97,  226, TOOLBAR_COLOR);
    draw_line(98,  227, HOR_MAX - 98,  227, TOOLBAR_COLOR);
    draw_line(100, 228, HOR_MAX - 100, 228, TOOLBAR_COLOR);
    draw_line(100, 229, HOR_MAX - 100, 229, TOOLBAR_COLOR);
    draw_line(103, 230, HOR_MAX - 103, 230, TOOLBAR_COLOR);
}

void draw_whole_note(int x_center, int y_center) {
    for (int i = -4; i < 5; i++)
        for (int j = -7; j < 8; j++)
            if (whole_note[i+4][j+7] == 1)
                plot_pixel(x_center + j, y_center + i, BLACK);
}

void draw_note(int x_center, int y_center) {
    for (int i = -4; i < 5; i++)
        for (int j = -7; j < 8; j++)
            if (note[i+4][j+7] == 1)
                plot_pixel(x_center + j, y_center + i, BLACK);
}

void draw_half_note(int x_center, int y_center) {
    draw_whole_note(x_center, y_center);
    if (y_center > staff_center)
        draw_line(x_center + 7, y_center, x_center + 7, y_center - 27, BLACK);
    else
        draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
}

void draw_quarter_note(int x_center, int y_center) {
    draw_note(x_center, y_center);
    if (y_center > staff_center)
        draw_line(x_center + 7, y_center, x_center + 7, y_center - 27, BLACK);
    else
        draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
}

void draw_eighth_note(int x_center, int y_center) {
    draw_quarter_note(x_center, y_center);
    draw_flag(x_center, y_center);
}

void draw_sixteenth_note(int x_center, int y_center) {
    draw_eighth_note(x_center, y_center);
    if (y_center > staff_center) draw_flag(x_center, y_center + 4);
    else                         draw_flag(x_center, y_center - 4);
}

void draw_ledger_line(int x_center, int y_center) {
    draw_line(x_center - 10, y_center, x_center + 11, y_center, BLACK);
}

void draw_flag(int x, int y) {
    if (y > staff_center) {
        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 5; j++)
                if (flag_up[i][j] == 1)
                    plot_pixel(x + 7 + j, y - 27 + i, BLACK);
    } else {
        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 5; j++)
                if (flag_down[i][j] == 1)
                    plot_pixel(x - 7 + j, y + 27 + i, BLACK);
    }
}