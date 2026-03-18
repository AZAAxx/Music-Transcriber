#include "../GLOBALS.h"
#include "../Adafruit/FreeMono9pt7b.h"
#include "../Adafruit/gfxfont.h"
#include "VGA.h"




void swap_buffers_on_vsync() {
    volatile int * pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;
    *pixel_ctrl_ptr = 1;                                // write 1 into the buffer reg to request a swap
    while (*(pixel_ctrl_ptr + 3) & 0x1);                // Wait until status.S turns 0
}




void plot_pixel(int x, int y, short int color){
    volatile short int *one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = color;
}



void background(int color){                            // iterate through every x, y
    for(int x = 0; x < 320; x++){
        for(int y = 0; y < 240; y++){
            plot_pixel(x, y, color);                   // paint it black
        }
    }
}



void VGA_init(){
    volatile int * pixel_ctrl_ptr = (int *) PIXEL_BUF_CTRL_BASE;

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;            // first store the address in the  back buffer
    swap_buffers_on_vsync();                           // swap the front/back buffers, to set the front buffer location
    pixel_buffer_start = *pixel_ctrl_ptr;              // set pixel_buffer_start to use in clear_screen()
    background(BLACK);                                 // clear the front buffer


    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);        // we draw on the back buffer
    background(BLACK); 

    CURSOR_Y = 50;                                     // arbitrary values for now
    CURSOR_X_DEFAULT = 10;
    CURSOR_X = CURSOR_X_DEFAULT;
}



void draw_char(const GFXfont *font, char c)
{
    if (c < font->first || c > font->last) return;

    const GFXglyph *glyph  = &font->glyph[c - font->first];
    const uint8_t  *bitmap = font->bitmap;

    uint16_t bit_offset = glyph->bitmapOffset * 8;                      // byte → bit index
    int gx = CURSOR_X + glyph->xOffset;
    int gy = CURSOR_Y + glyph->yOffset;                                 // yOffset is negative — goes above baseline

    for (int row = 0; row < glyph->height; row++) {
        for (int col = 0; col < glyph->width; col++) {
            uint16_t b = bit_offset + row * glyph->width + col;         // calculate the position of the bit within the bitmap
           
            if (bitmap[b / 8] & (0x80 >> (b % 8))) {                    // Extract the bit: MSB first within each byte
                plot_pixel(gx + col, gy + row, WHITE);
            }
        }
    }
}



void write(const GFXfont *font, const char *str)
{
    while (*str) {
        char c = *str++;
        if (c == '\n') {                                        // if there is a newline
            CURSOR_Y += font->yAdvance;                         // increment Y to go to the next line and reset the X position 
            CURSOR_X = CURSOR_X_DEFAULT;
            continue;
        }
        draw_char(font, c);                                     // draw the char
        
        CURSOR_X += font->glyph[c - font->first].xAdvance;             // advance cursor by the glyph's xAdvance
    }
}




