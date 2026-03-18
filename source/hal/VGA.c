#include "hal/VGA.h"
#include "GLOBALS.h"

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



void draw_whole_note(int x_center, int y_center) {
    
}
void draw_half_note(int x_center, int y_center);
void draw_quarter_note(int x_center, int y_center);
void draw_eighth_note(int x_center, int y_center);
void draw_sixteenth_note(int x_center, int y_center);
void draw_ledger_line(int x_center, int y_center);



void draw_staff(int x, int y) { // 5 lines in staff
    draw_brace(x - 8, y);
    draw_line(x, y, 319 - x, y, BLACK);
    draw_line(x, y + 9, 319 - x, y + 9, BLACK);
    draw_line(x, y + 18, 319 - x, y + 18, BLACK);
    draw_line(x, y + 27, 319 - x, y + 27, BLACK);
    draw_line(x, y + 36, 319 - x, y + 36, BLACK);
    
    draw_treble_clef(x, y);
    draw_time_signature(x, y);
}

void draw_brace(int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 5; j++) {
            if (brace[i][j] == 1) {
                plot_pixel(x + i, y + j, BLACK);
            }
        }
    }
}

void draw_bar_line(int x_center, int y_center) {
    draw_line(x_center, y_center, x_center, y_center + 36);
}

void draw_treble_clef(int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 12; j++) {
            if (treble_clef[i][j] == 1) {
                plot_pixel(x + i, y + j, BLACK);
            }
        }
    }
}

void draw_time_signature(int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 5; j++) {
            if (time_sig_4_4[i][j] == 1) {
                plot_pixel(x + i, y + j, BLACK);
            }
        }
    }
}

void draw_toolbar() {
    draw_line(210, 120, 210, 312 - 120, BLACK);
    draw_line(211, 119, 211, 312 - 119, BLACK);
    draw_line(212, 118, 212, 312 - 118, BLACK);
    int count = 0;
    for (int i = 213; i < 228; i++) {
        draw_line(i + count, 117, i + count, 312 - 117, BLACK);
        count++;
    }
    draw_line(228, 118, 228, 312 - 118, BLACK);
    draw_line(229, 119, 229, 312 - 119, BLACK);
    draw_line(230, 120, 230, 312 - 120, BLACK);
}