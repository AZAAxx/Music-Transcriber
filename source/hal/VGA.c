#include "../Adafruit/FreeMono9pt7b.h"
#include "../Adafruit/gfxfont.h"
#include "VGA.h"
#include <stdbool.h>


void swap_buffers_on_vsync() {
    pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;
    *pixel_ctrl_ptr = 1;                                // write 1 into the buffer reg to request a swap
    while (*(pixel_ctrl_ptr + 3) & 0x1);                // Wait until status.S turns 0
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



void VGA_init(){
    pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;            // first store the address in the  back buffer
    swap_buffers_on_vsync();                           // swap the front/back buffers, to set the front buffer location
    pixel_buffer_start = *pixel_ctrl_ptr;              // set pixel_buffer_start to use in clear_screen()
    background(BLACK);                                 // clear the front buffer


    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);        // we draw on the back buffer
    background(BLACK); 

    CURSOR_Y_DEFAULT = 20;                             // arbitrary values for now
    CURSOR_X_DEFAULT = 10;
    CURSOR_Y = CURSOR_Y_DEFAULT;
    CURSOR_X = CURSOR_X_DEFAULT;
}


/* Used for Terminal.c */

void draw_char(char c, short int color)
{
    const GFXfont *font = &FONT;

    if (c < font->first || c > font->last) return;

    const GFXglyph *glyph  = &font->glyph[c - font->first];
    const uint8_t  *bitmap = font->bitmap;

    uint16_t bit_offset = glyph->bitmapOffset * 8;                 // byte → bit index
    int gx = CURSOR_X + glyph->xOffset;
    int gy = CURSOR_Y + glyph->yOffset;                            // yOffset is negative — goes above baseline

    for (int row = 0; row < glyph->height; row++) {
        for (int col = 0; col < glyph->width; col++) {
            uint16_t b = bit_offset + row * glyph->width + col;         // calculate the position of the bit within the bitmap
           
            if (bitmap[b / 8] & (0x80 >> (b % 8))) {                    // Extract the bit: MSB first within each byte
                plot_pixel(gx + col, gy + row, color);
            }
        }
    }
}


/* ONLY USE THIS FUNCTION TO WRITE STUFF */
void write(const char * str){
    const GFXfont *font = &FONT;

    while (*str != '\0') {             // while it is not the terminating character yet
        char c = *str++;

        if (c == '\n') {                                  // if there is a newline
            CURSOR_Y += font->yAdvance;                   // increment Y to go to the next line and reset the X position 
            CURSOR_X = CURSOR_X_DEFAULT;
            continue;
        }

        if (c < font->first || c > font->last) continue;
        
        draw_char(c, WHITE);  
        swap_buffers_on_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);       // change to back buffer
        draw_char(c, WHITE);  

        const GFXglyph *glyph  = &font->glyph[c - font->first];
        CURSOR_X += glyph->xAdvance;
    }
}



void delete(char c){
    const GFXfont *font = &FONT;
    const GFXglyph *glyph  = &font->glyph[c - font->first];
    CURSOR_X -= glyph->xAdvance;

    draw_char(c, BLACK);  
    swap_buffers_on_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);       // change to back buffer
    draw_char(c, BLACK);  
}







/* All below is used for score.c */

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
        for (int j = 0; j < 5; j++) {
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
    }
    else draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
}

void draw_quarter_note(int x_center, int y_center) {
    draw_note(x_center, y_center);
    if (y_center > staff_center) {
        draw_line(x_center + 7, y_center, x_center + 7, y_center - 27, BLACK);
    }
    else draw_line(x_center - 7, y_center, x_center - 7, y_center + 27, BLACK);
}

void draw_eighth_note(int x_center, int y_center) {
    draw_quarter_note(x_center, y_center);
    draw_flag(x_center, y_center);
}

void draw_sixteenth_note(int x_center, int y_center) {
    draw_eighth_note(x_center, y_center);
	if (y_center > staff_center) {
		draw_flag(x_center, y_center + 4);
	}
	else draw_flag(x_center, y_center - 4);
}

void draw_ledger_line(int x_center, int y_center) {
    draw_line(x_center - 10, y_center, x_center + 11, y_center, BLACK);
}

void draw_flag(int x, int y) { // x and y are start of flag
    if (y > staff_center) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 5; j++) {
                if (flag_up[i][j] == 1) {
                    plot_pixel(x + 7 + j, y - 27 + i, BLACK);
                }
            }
        }      
    }
    else {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 5; j++) {
                if (flag_down[i][j] == 1) {
                    plot_pixel(x - 7 + j, y + 27 + i, BLACK);
                }
            }
        }  
    }
}
