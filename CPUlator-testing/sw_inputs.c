#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
	
#define VGA_BASE 0xFF203020
#define KEY_BASE ((volatile int*)0xFF200050)
#define SW_BASE 0xFF200040

volatile unsigned int *SW = (unsigned int*)SW_BASE;
	
const short int WHITE = 0xFFFF;
const short int BLACK = 0x0000;
const short int TOOLBAR_COLOR = 0x731F; // this is light purple right now

volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

const int VERT_MIN = 0;
const int VERT_MAX = 239; 
const int HOR_MIN = 0;
const int HOR_MAX = 319; 

int staff_center;
char note_type;

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

int treble_clef[44][16] = { // center around G better
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

int time_sig_4_4[36][8] = { // looks a little funny right now, fix later
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
    {0,0,0,0,1,1,1,1}, // line 18
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
    {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1}, // center line
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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // center line
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

void plot_pixel(int x, int y, short int color);
void background(short int color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);
void wait_for_vsync();

void draw_staff(int x, int y); // x, y is starting position
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
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;

    *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // set front pixel buffer to Buffer1, store address in back buffer
    wait_for_vsync(); // swap front/back buffers
    pixel_buffer_start = *pixel_ctrl_ptr; // initialize pointer to pixel
    background(WHITE); // pixel_buffer_start points to the pixel buffer

    *(pixel_ctrl_ptr + 1) = (int) &Buffer2; // back pixel buffer = Buffer2
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // draw on the back buffer
    background(WHITE); // pixel_buffer_start points to the pixel buffer
	
    // initialize score (staff, clef, time signature)
    draw_staff(15, 30);
	draw_time_signature(32, 30);
    draw_toolbar();
	
	wait_for_vsync(); // swap front and back buffers on VGA vertical sync
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

    // setting up keys
    int edge_cap;
	bool note_drawn = false;
	
	// setting up position
    int current_hor = 60;
    int current_vert = 30+27;
	staff_center = 30+18; // temp
	
    // loop which detects new inputs and draws them
    while (1) {
        // detect edge case for button press -> make sure that SW[0] is on too
        unsigned int sw = *SW & 0x3FF; // sw will hold what switches are on or off
		
		if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3); // checking for any if any keys pressed
            if (edge_cap & 0xF) { // if any KEY[3:0] pressed
				note_drawn = true;
				if (edge_cap & 0x1) {
					note_type = 'w';
				}	
				else if (edge_cap & 0x2) {
					note_type = 'q';	
				}
				else if (edge_cap & 0x4) {
					note_type = 'e';
				}
				else if (edge_cap & 0x8) {
					note_type = 's';
				}
				
				if (sw & 0x2) { // SW[1] = C
					current_vert = staff_center + 27;
				}	
				if (sw & 0x4) { // SW[2] = D
					current_vert = staff_center + 23;
				}
				if (sw & 0x8) { // SW[3] = E
					current_vert = staff_center + 18;
				}	
				if (sw & 0x10) { // SW[4] = F
					current_vert = staff_center + 13;
				}
				if (sw & 0x20) { // SW[5] = G
					current_vert = staff_center + 9;
				}
				if (sw & 0x40) { // SW[6] = A
					current_vert = staff_center + 5;
				}
				if (sw & 0x80) { // SW[7] = B
					current_vert = staff_center;
				}
				if (sw & 0x100) { // SW[8] = C but higher octave
					current_vert = staff_center - 5;
				}
            }
        }  
		
		*(KEY_BASE + 3) = 0x3FF; // reset edge capture register
		
		//background(WHITE);
		draw_staff(15, 30);
		draw_time_signature(32, 30);
		draw_toolbar();
		
		if (note_drawn) {
            if (sw & 0x2) {
                draw_ledger_line(current_hor, current_vert);
            }
			if (note_type == 'w') {
				draw_whole_note(current_hor, current_vert);
			}
			else if (note_type == 'h') {
				draw_half_note(current_hor, current_vert);
			}
			else if (note_type == 'q') {
				draw_quarter_note(current_hor, current_vert);
			}
			else if (note_type == 'e') {
				draw_eighth_note(current_hor, current_vert);
			}
			else if (note_type == 's') {
				draw_sixteenth_note(current_hor, current_vert);
			}
		}
				
		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

		if (note_drawn) {
            if (sw & 0x2) {
                draw_ledger_line(current_hor, current_vert);
            }
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
	}
}

void plot_pixel(int x, int y, short int color) {
    volatile short int *one_pixel_address;
        
        one_pixel_address = (short int*) (pixel_buffer_start + (y << 10) + (x << 1));
        
        *one_pixel_address = color;
}

void background(short int color) {
	for (int x = 0; x < 320; x++) {
		for (int y = 0; y < 240; y++) {
			plot_pixel(x, y, color); 
		}
	}
	return;
}

void draw_line(int x0, int y0, int x1, int y1, short int color) {
	bool is_steep = abs(y1 - y0) > abs (x1 - x0);
	if (is_steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}	
	
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	int error = -(deltax / 2);
	int y = y0;
	int y_step;
	
	if (y0 < y1) {
		y_step = 1;
	}
	else { y_step = -1; }
	
	for (int x = x0; x < x1; x++) {
		if (is_steep) {
			plot_pixel(y, x, color);	
		}
		else {
			plot_pixel(x, y, color);
		}
		error += deltay;
		if (error > 0) {
			y += y_step;
			error -= deltax;
		}
	}
	
	return;
}	

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void wait_for_vsync() {
	volatile int * pixel_ctrl_ptr = (int *) VGA_BASE;
	*pixel_ctrl_ptr = 1; // Request a swap
	while (*(pixel_ctrl_ptr + 3) & 0x1); // Wait for S bit (swap pending) bit to go to 0
}



void draw_staff(int x, int y) { 
    draw_line(x, y, HOR_MAX - x, y, BLACK); // 5 lines in staff
    draw_line(x, y + 9, HOR_MAX - x, y + 9, BLACK);
    draw_line(x, y + 18, HOR_MAX - x, y + 18, BLACK);
    draw_line(x, y + 27, HOR_MAX - x, y + 27, BLACK);
    draw_line(x, y + 36, HOR_MAX - x, y + 36, BLACK);
	
    draw_brace(x - 8, y);
    draw_treble_clef(x, y - 4);
	draw_bar_line(x, y); // first bar line near treble clef
	draw_bar_line(HOR_MAX - x - 1, y); // end of line
}

void draw_brace(int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 5; j++) {
            if (brace[i][j] == 1) {
                plot_pixel(x + j, y + i, BLACK);
            }
        }
    }
}

void draw_bar_line(int x_center, int y_center) {
    draw_line(x_center, y_center, x_center, y_center + 36, BLACK);
}

void draw_treble_clef(int x, int y) {
    for (int i = 0; i < 44; i++) {
        for (int j = 0; j < 16; j++) {
            if (treble_clef[i][j] == 1) {
                plot_pixel(x + j, y + i, BLACK);
            }
        }
    }
}

void draw_time_signature(int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 8; j++) {
            if (time_sig_4_4[i][j] == 1) {
                plot_pixel(x + j, y + i, BLACK);
            }
        }
    }
}

void draw_toolbar() {
    draw_line(103, 210, HOR_MAX - 103, 210, TOOLBAR_COLOR);
    draw_line(100, 211, HOR_MAX - 100, 211, TOOLBAR_COLOR);
	draw_line(100, 212, HOR_MAX - 100, 212, TOOLBAR_COLOR);
    draw_line(98, 213, HOR_MAX - 98, 213, TOOLBAR_COLOR);
	draw_line(97, 214, HOR_MAX - 97, 214, TOOLBAR_COLOR);
	draw_line(97, 215, HOR_MAX - 97, 215, TOOLBAR_COLOR);
	
    int count = 0;
    for (int i = 216; i < 225; i++) {
        draw_line(96, i, HOR_MAX - 96, i, TOOLBAR_COLOR);
        count++;
    }
	
	draw_line(97, 225, HOR_MAX - 97, 225, TOOLBAR_COLOR);
	draw_line(97, 226, HOR_MAX - 97, 226, TOOLBAR_COLOR);
    draw_line(98, 227, HOR_MAX - 98, 227, TOOLBAR_COLOR);
	draw_line(100, 228, HOR_MAX - 100, 228, TOOLBAR_COLOR);
    draw_line(100, 229, HOR_MAX - 100, 229, TOOLBAR_COLOR);
    draw_line(103, 230, HOR_MAX - 103, 230, TOOLBAR_COLOR);
}

void draw_whole_note(int x_center, int y_center) {
    for (int i = -4; i < 5; i++) {
        for (int j = -7; j < 8; j++) {
            if (whole_note[i+4][j+7] == 1) {
                plot_pixel(x_center + j, y_center + i, BLACK);
            }
        }
    }
}

void draw_note(int x_center, int y_center) {
    for (int i = -4; i < 5; i++) {
        for (int j = -7; j < 8; j++) {
            if (note[i+4][j+7] == 1) {
                plot_pixel(x_center + j, y_center + i, BLACK);
            }
        }
    }    
}

void draw_half_note(int x_center, int y_center) {
    draw_whole_note(x_center, y_center);
    if (y_center > staff_center) {
        draw_line(x_center + 7, y_center, x_center + 7, y_center - 27, BLACK);
		draw_line(x_center + 6, y_center, x_center + 6, y_center - 27, BLACK);
    }
    else {
		draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
		draw_line(x_center - 6, y_center, x_center - 6, y_center + 27, BLACK);
	}
}

void draw_quarter_note(int x_center, int y_center) {
    draw_note(x_center, y_center);
    if (y_center > staff_center) {
        draw_line(x_center + 7, y_center, x_center + 7, y_center - 27, BLACK);
		draw_line(x_center + 6, y_center, x_center + 6, y_center - 27, BLACK);
    }
    else {
		draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
		draw_line(x_center - 6, y_center, x_center - 6, y_center + 27, BLACK);
	}
}

void draw_eighth_note(int x_center, int y_center) {
    draw_quarter_note(x_center, y_center);
    draw_flag(x_center, y_center);
}

void draw_sixteenth_note(int x_center, int y_center) {
    draw_eighth_note(x_center, y_center);
	if (y_center > staff_center) {
		draw_flag(x_center, y_center + 8);
	}
	else draw_flag(x_center, y_center - 8);
}

void draw_ledger_line(int x_center, int y_center) {
    draw_line(x_center - 10, y_center, x_center + 11, y_center, BLACK);
}

void draw_flag(int x, int y) { // x and y are start of flag
    if (y > staff_center) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 8; j++) {
                if (flag_up[i][j] == 1) {
                    plot_pixel(x + 7 + j, y - 27 + i, BLACK);
                }
            }
        }      
    }
    else {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 15; j++) {
                if (flag_down[i][j] == 1) {
                    plot_pixel(x - 7 + j, y + 27 - 12 + i, BLACK);
                }
            }
        }  
    }
}