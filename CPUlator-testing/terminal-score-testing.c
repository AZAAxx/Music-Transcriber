#ifndef _GFXFONT_H_
#define _GFXFONT_H_
#include <stdint.h>

/// Font data stored PER GLYPH
typedef struct {
  uint16_t bitmapOffset; ///< Pointer into GFXfont->bitmap
  uint8_t width;         ///< Bitmap dimensions in pixels
  uint8_t height;        ///< Bitmap dimensions in pixels
  uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
  int8_t xOffset;        ///< X dist from cursor pos to UL corner
  int8_t yOffset;        ///< Y dist from cursor pos to UL corner
} GFXglyph;

/// Data stored for FONT AS A WHOLE
typedef struct {
  uint8_t *bitmap;  ///< Glyph bitmaps, concatenated
  GFXglyph *glyph;  ///< Glyph array
  uint16_t first;   ///< ASCII extents (first char)
  uint16_t last;    ///< ASCII extents (last char)
  uint8_t yAdvance; ///< Newline distance (y axis)
} GFXfont;

#endif // _GFXFONT_H_



//#pragma once
//#include <Adafruit_GFX.h>

const uint8_t FreeMono9pt7bBitmaps[] = {
    0xAA, 0xA8, 0x0C, 0xED, 0x24, 0x92, 0x48, 0x24, 0x48, 0x91, 0x2F, 0xE4,
    0x89, 0x7F, 0x28, 0x51, 0x22, 0x40, 0x08, 0x3E, 0x62, 0x40, 0x30, 0x0E,
    0x01, 0x81, 0xC3, 0xBE, 0x08, 0x08, 0x71, 0x12, 0x23, 0x80, 0x23, 0xB8,
    0x0E, 0x22, 0x44, 0x70, 0x38, 0x81, 0x02, 0x06, 0x1A, 0x65, 0x46, 0xC8,
    0xEC, 0xE9, 0x24, 0x5A, 0xAA, 0xA9, 0x40, 0xA9, 0x55, 0x5A, 0x80, 0x10,
    0x22, 0x4B, 0xE3, 0x05, 0x11, 0x00, 0x10, 0x20, 0x47, 0xF1, 0x02, 0x04,
    0x00, 0x6B, 0x48, 0xFF, 0x00, 0xF0, 0x02, 0x08, 0x10, 0x60, 0x81, 0x04,
    0x08, 0x20, 0x41, 0x02, 0x08, 0x00, 0x38, 0x8A, 0x0C, 0x18, 0x30, 0x60,
    0xC1, 0x82, 0x88, 0xE0, 0x27, 0x28, 0x42, 0x10, 0x84, 0x21, 0x3E, 0x38,
    0x8A, 0x08, 0x10, 0x20, 0x82, 0x08, 0x61, 0x03, 0xF8, 0x7C, 0x06, 0x02,
    0x02, 0x1C, 0x06, 0x01, 0x01, 0x01, 0x42, 0x3C, 0x18, 0xA2, 0x92, 0x8A,
    0x28, 0xBF, 0x08, 0x21, 0xC0, 0x7C, 0x81, 0x03, 0xE4, 0x40, 0x40, 0x81,
    0x03, 0x88, 0xE0, 0x1E, 0x41, 0x04, 0x0B, 0x98, 0xB0, 0xC1, 0xC2, 0x88,
    0xE0, 0xFE, 0x04, 0x08, 0x20, 0x40, 0x82, 0x04, 0x08, 0x20, 0x40, 0x38,
    0x8A, 0x0C, 0x14, 0x47, 0x11, 0x41, 0x83, 0x8C, 0xE0, 0x38, 0x8A, 0x1C,
    0x18, 0x68, 0xCE, 0x81, 0x04, 0x13, 0xC0, 0xF0, 0x0F, 0x6C, 0x00, 0xD2,
    0xD2, 0x00, 0x03, 0x04, 0x18, 0x60, 0x60, 0x18, 0x04, 0x03, 0xFF, 0x80,
    0x00, 0x1F, 0xF0, 0x40, 0x18, 0x03, 0x00, 0x60, 0x20, 0x60, 0xC0, 0x80,
    0x3D, 0x84, 0x08, 0x30, 0xC2, 0x00, 0x00, 0x00, 0x30, 0x3C, 0x46, 0x82,
    0x8E, 0xB2, 0xA2, 0xA2, 0x9F, 0x80, 0x80, 0x40, 0x3C, 0x3C, 0x01, 0x40,
    0x28, 0x09, 0x01, 0x10, 0x42, 0x0F, 0xC1, 0x04, 0x40, 0x9E, 0x3C, 0xFE,
    0x21, 0x90, 0x48, 0x67, 0xE2, 0x09, 0x02, 0x81, 0x41, 0xFF, 0x80, 0x3E,
    0xB0, 0xF0, 0x30, 0x08, 0x04, 0x02, 0x00, 0x80, 0x60, 0x8F, 0x80, 0xFE,
    0x21, 0x90, 0x68, 0x14, 0x0A, 0x05, 0x02, 0x83, 0x43, 0x7F, 0x00, 0xFF,
    0x20, 0x90, 0x08, 0x87, 0xC2, 0x21, 0x00, 0x81, 0x40, 0xFF, 0xC0, 0xFF,
    0xA0, 0x50, 0x08, 0x87, 0xC2, 0x21, 0x00, 0x80, 0x40, 0x78, 0x00, 0x1E,
    0x98, 0x6C, 0x0A, 0x00, 0x80, 0x20, 0xF8, 0x0B, 0x02, 0x60, 0x87, 0xC0,
    0xE3, 0xA0, 0x90, 0x48, 0x27, 0xF2, 0x09, 0x04, 0x82, 0x41, 0x71, 0xC0,
    0xF9, 0x08, 0x42, 0x10, 0x84, 0x27, 0xC0, 0x1F, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x82, 0x82, 0xC6, 0x78, 0xE3, 0xA1, 0x11, 0x09, 0x05, 0x83, 0x21,
    0x08, 0x84, 0x41, 0x70, 0xC0, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41,
    0x41, 0x41, 0xFF, 0xE0, 0xEC, 0x19, 0x45, 0x28, 0xA4, 0xA4, 0x94, 0x91,
    0x12, 0x02, 0x40, 0x5C, 0x1C, 0xC3, 0xB0, 0x94, 0x4A, 0x24, 0x92, 0x49,
    0x14, 0x8A, 0x43, 0x70, 0x80, 0x1E, 0x31, 0x90, 0x50, 0x18, 0x0C, 0x06,
    0x02, 0x82, 0x63, 0x0F, 0x00, 0xFE, 0x43, 0x41, 0x41, 0x42, 0x7C, 0x40,
    0x40, 0x40, 0xF0, 0x1C, 0x31, 0x90, 0x50, 0x18, 0x0C, 0x06, 0x02, 0x82,
    0x63, 0x1F, 0x04, 0x07, 0x92, 0x30, 0xFE, 0x21, 0x90, 0x48, 0x24, 0x23,
    0xE1, 0x10, 0x84, 0x41, 0x70, 0xC0, 0x3A, 0xCD, 0x0A, 0x03, 0x01, 0x80,
    0xC1, 0xC7, 0x78, 0xFF, 0xC4, 0x62, 0x21, 0x00, 0x80, 0x40, 0x20, 0x10,
    0x08, 0x1F, 0x00, 0xE3, 0xA0, 0x90, 0x48, 0x24, 0x12, 0x09, 0x04, 0x82,
    0x22, 0x0E, 0x00, 0xF1, 0xE8, 0x10, 0x82, 0x10, 0x42, 0x10, 0x22, 0x04,
    0x80, 0x50, 0x0C, 0x00, 0x80, 0xF1, 0xE8, 0x09, 0x11, 0x25, 0x44, 0xA8,
    0x55, 0x0C, 0xA1, 0x8C, 0x31, 0x84, 0x30, 0xE3, 0xA0, 0x88, 0x82, 0x80,
    0x80, 0xC0, 0x90, 0x44, 0x41, 0x71, 0xC0, 0xE3, 0xA0, 0x88, 0x82, 0x81,
    0x40, 0x40, 0x20, 0x10, 0x08, 0x1F, 0x00, 0xFD, 0x0A, 0x20, 0x81, 0x04,
    0x10, 0x21, 0x83, 0xFC, 0xEA, 0xAA, 0xAA, 0xC0, 0x80, 0x81, 0x03, 0x02,
    0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0xD5, 0x55, 0x55, 0xC0,
    0x10, 0x51, 0x22, 0x28, 0x20, 0xFF, 0xE0, 0x88, 0x80, 0x7E, 0x00, 0x80,
    0x47, 0xEC, 0x14, 0x0A, 0x0C, 0xFB, 0xC0, 0x20, 0x10, 0x0B, 0xC6, 0x12,
    0x05, 0x02, 0x81, 0x40, 0xB0, 0xB7, 0x80, 0x3A, 0x8E, 0x0C, 0x08, 0x10,
    0x10, 0x9E, 0x03, 0x00, 0x80, 0x47, 0xA4, 0x34, 0x0A, 0x05, 0x02, 0x81,
    0x21, 0x8F, 0x60, 0x3C, 0x43, 0x81, 0xFF, 0x80, 0x80, 0x61, 0x3E, 0x3D,
    0x04, 0x3E, 0x41, 0x04, 0x10, 0x41, 0x0F, 0x80, 0x3D, 0xA1, 0xA0, 0x50,
    0x28, 0x14, 0x09, 0x0C, 0x7A, 0x01, 0x01, 0x87, 0x80, 0xC0, 0x20, 0x10,
    0x0B, 0xC6, 0x32, 0x09, 0x04, 0x82, 0x41, 0x20, 0xB8, 0xE0, 0x10, 0x01,
    0xC0, 0x81, 0x02, 0x04, 0x08, 0x11, 0xFC, 0x10, 0x3E, 0x10, 0x84, 0x21,
    0x08, 0x42, 0x3F, 0x00, 0xC0, 0x40, 0x40, 0x4F, 0x44, 0x58, 0x70, 0x48,
    0x44, 0x42, 0xC7, 0x70, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x23,
    0xF8, 0xB7, 0x64, 0x62, 0x31, 0x18, 0x8C, 0x46, 0x23, 0x91, 0x5E, 0x31,
    0x90, 0x48, 0x24, 0x12, 0x09, 0x05, 0xC7, 0x3E, 0x31, 0xA0, 0x30, 0x18,
    0x0C, 0x05, 0x8C, 0x7C, 0xDE, 0x30, 0x90, 0x28, 0x14, 0x0A, 0x05, 0x84,
    0xBC, 0x40, 0x20, 0x38, 0x00, 0x3D, 0xA1, 0xA0, 0x50, 0x28, 0x14, 0x09,
    0x0C, 0x7A, 0x01, 0x00, 0x80, 0xE0, 0xCE, 0xA1, 0x82, 0x04, 0x08, 0x10,
    0x7C, 0x3A, 0x8D, 0x0B, 0x80, 0xF0, 0x70, 0xDE, 0x40, 0x40, 0xFC, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x41, 0x3E, 0xC3, 0x41, 0x41, 0x41, 0x41, 0x41,
    0x43, 0x3D, 0xE3, 0xA0, 0x90, 0x84, 0x42, 0x20, 0xA0, 0x50, 0x10, 0xE3,
    0xC0, 0x92, 0x4B, 0x25, 0x92, 0xA9, 0x98, 0x44, 0xE3, 0x31, 0x05, 0x01,
    0x01, 0x41, 0x11, 0x05, 0xC7, 0xE3, 0xA0, 0x90, 0x84, 0x42, 0x40, 0xA0,
    0x60, 0x10, 0x10, 0x08, 0x3E, 0x00, 0xFD, 0x08, 0x20, 0x82, 0x08, 0x10,
    0xBF, 0x29, 0x24, 0xA2, 0x49, 0x26, 0xFF, 0xF8, 0x89, 0x24, 0x8A, 0x49,
    0x2C, 0x61, 0x24, 0x30};

const GFXglyph FreeMono9pt7bGlyphs[] = {
    {0, 0, 0, 11, 0, 1},      // 0x20 ' '
    {0, 2, 11, 11, 4, -10},   // 0x21 '!'
    {3, 6, 5, 11, 2, -10},    // 0x22 '"'
    {7, 7, 12, 11, 2, -10},   // 0x23 '#'
    {18, 8, 12, 11, 1, -10},  // 0x24 '$'
    {30, 7, 11, 11, 2, -10},  // 0x25 '%'
    {40, 7, 10, 11, 2, -9},   // 0x26 '&'
    {49, 3, 5, 11, 4, -10},   // 0x27 '''
    {51, 2, 13, 11, 5, -10},  // 0x28 '('
    {55, 2, 13, 11, 4, -10},  // 0x29 ')'
    {59, 7, 7, 11, 2, -10},   // 0x2A '*'
    {66, 7, 7, 11, 2, -8},    // 0x2B '+'
    {73, 3, 5, 11, 2, -1},    // 0x2C ','
    {75, 9, 1, 11, 1, -5},    // 0x2D '-'
    {77, 2, 2, 11, 4, -1},    // 0x2E '.'
    {78, 7, 13, 11, 2, -11},  // 0x2F '/'
    {90, 7, 11, 11, 2, -10},  // 0x30 '0'
    {100, 5, 11, 11, 3, -10}, // 0x31 '1'
    {107, 7, 11, 11, 2, -10}, // 0x32 '2'
    {117, 8, 11, 11, 1, -10}, // 0x33 '3'
    {128, 6, 11, 11, 3, -10}, // 0x34 '4'
    {137, 7, 11, 11, 2, -10}, // 0x35 '5'
    {147, 7, 11, 11, 2, -10}, // 0x36 '6'
    {157, 7, 11, 11, 2, -10}, // 0x37 '7'
    {167, 7, 11, 11, 2, -10}, // 0x38 '8'
    {177, 7, 11, 11, 2, -10}, // 0x39 '9'
    {187, 2, 8, 11, 4, -7},   // 0x3A ':'
    {189, 3, 11, 11, 3, -7},  // 0x3B ';'
    {194, 8, 8, 11, 1, -8},   // 0x3C '<'
    {202, 9, 4, 11, 1, -6},   // 0x3D '='
    {207, 9, 8, 11, 1, -8},   // 0x3E '>'
    {216, 7, 10, 11, 2, -9},  // 0x3F '?'
    {225, 8, 12, 11, 2, -10}, // 0x40 '@'
    {237, 11, 10, 11, 0, -9}, // 0x41 'A'
    {251, 9, 10, 11, 1, -9},  // 0x42 'B'
    {263, 9, 10, 11, 1, -9},  // 0x43 'C'
    {275, 9, 10, 11, 1, -9},  // 0x44 'D'
    {287, 9, 10, 11, 1, -9},  // 0x45 'E'
    {299, 9, 10, 11, 1, -9},  // 0x46 'F'
    {311, 10, 10, 11, 1, -9}, // 0x47 'G'
    {324, 9, 10, 11, 1, -9},  // 0x48 'H'
    {336, 5, 10, 11, 3, -9},  // 0x49 'I'
    {343, 8, 10, 11, 2, -9},  // 0x4A 'J'
    {353, 9, 10, 11, 1, -9},  // 0x4B 'K'
    {365, 8, 10, 11, 2, -9},  // 0x4C 'L'
    {375, 11, 10, 11, 0, -9}, // 0x4D 'M'
    {389, 9, 10, 11, 1, -9},  // 0x4E 'N'
    {401, 9, 10, 11, 1, -9},  // 0x4F 'O'
    {413, 8, 10, 11, 1, -9},  // 0x50 'P'
    {423, 9, 13, 11, 1, -9},  // 0x51 'Q'
    {438, 9, 10, 11, 1, -9},  // 0x52 'R'
    {450, 7, 10, 11, 2, -9},  // 0x53 'S'
    {459, 9, 10, 11, 1, -9},  // 0x54 'T'
    {471, 9, 10, 11, 1, -9},  // 0x55 'U'
    {483, 11, 10, 11, 0, -9}, // 0x56 'V'
    {497, 11, 10, 11, 0, -9}, // 0x57 'W'
    {511, 9, 10, 11, 1, -9},  // 0x58 'X'
    {523, 9, 10, 11, 1, -9},  // 0x59 'Y'
    {535, 7, 10, 11, 2, -9},  // 0x5A 'Z'
    {544, 2, 13, 11, 5, -10}, // 0x5B '['
    {548, 7, 13, 11, 2, -11}, // 0x5C '\'
    {560, 2, 13, 11, 4, -10}, // 0x5D ']'
    {564, 7, 5, 11, 2, -10},  // 0x5E '^'
    {569, 11, 1, 11, 0, 2},   // 0x5F '_'
    {571, 3, 3, 11, 3, -11},  // 0x60 '`'
    {573, 9, 8, 11, 1, -7},   // 0x61 'a'
    {582, 9, 11, 11, 1, -10}, // 0x62 'b'
    {595, 7, 8, 11, 2, -7},   // 0x63 'c'
    {602, 9, 11, 11, 1, -10}, // 0x64 'd'
    {615, 8, 8, 11, 1, -7},   // 0x65 'e'
    {623, 6, 11, 11, 3, -10}, // 0x66 'f'
    {632, 9, 11, 11, 1, -7},  // 0x67 'g'
    {645, 9, 11, 11, 1, -10}, // 0x68 'h'
    {658, 7, 10, 11, 2, -9},  // 0x69 'i'
    {667, 5, 13, 11, 3, -9},  // 0x6A 'j'
    {676, 8, 11, 11, 2, -10}, // 0x6B 'k'
    {687, 7, 11, 11, 2, -10}, // 0x6C 'l'
    {697, 9, 8, 11, 1, -7},   // 0x6D 'm'
    {706, 9, 8, 11, 1, -7},   // 0x6E 'n'
    {715, 9, 8, 11, 1, -7},   // 0x6F 'o'
    {724, 9, 11, 11, 1, -7},  // 0x70 'p'
    {737, 9, 11, 11, 1, -7},  // 0x71 'q'
    {750, 7, 8, 11, 3, -7},   // 0x72 'r'
    {757, 7, 8, 11, 2, -7},   // 0x73 's'
    {764, 8, 10, 11, 2, -9},  // 0x74 't'
    {774, 8, 8, 11, 1, -7},   // 0x75 'u'
    {782, 9, 8, 11, 1, -7},   // 0x76 'v'
    {791, 9, 8, 11, 1, -7},   // 0x77 'w'
    {800, 9, 8, 11, 1, -7},   // 0x78 'x'
    {809, 9, 11, 11, 1, -7},  // 0x79 'y'
    {822, 7, 8, 11, 2, -7},   // 0x7A 'z'
    {829, 3, 13, 11, 4, -10}, // 0x7B '{'
    {834, 1, 13, 11, 5, -10}, // 0x7C '|'
    {836, 3, 13, 11, 4, -10}, // 0x7D '}'
    {841, 7, 3, 11, 2, -6}};  // 0x7E '~'

const GFXfont FreeMono9pt7b = {(uint8_t *)FreeMono9pt7bBitmaps,
                                       (GFXglyph *)FreeMono9pt7bGlyphs, 0x20,
                                       0x7E, 18};

// Approx. 1516 bytes


/* VGA.c and VGA.h CONTENT */

#define PIXEL_BUF_CTRL_BASE		0xFF203020

const short int BLACK = 0x0000;
const short int WHITE = 0xFFFF;


int CURSOR_Y_DEFAULT;                      // arbitrary values for now
int CURSOR_X_DEFAULT;
int CURSOR_Y;
int CURSOR_X;

#define FONT FreeMono9pt7b                   // global font when not specified otherwise


volatile int * pixel_ctrl_ptr;
volatile int pixel_buffer_start;              // global variable
short int Buffer1[240][512];                  // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];


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

    CURSOR_Y_DEFAULT = 50;                             // arbitrary values for now
    CURSOR_X_DEFAULT = 10;
    CURSOR_Y = CURSOR_Y_DEFAULT;
    CURSOR_X = CURSOR_X_DEFAULT;
}

void draw_char(char c)
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
                plot_pixel(gx + col, gy + row, WHITE);
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
        
        draw_char(c);  
        swap_buffers_on_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);       // change to back buffer
        draw_char(c);  

        const GFXglyph *glyph  = &font->glyph[c - font->first];
        CURSOR_X += glyph->xAdvance;
    }
}

/* PS2.c and PS2.h CONTENT */

#include  <stdlib.h>
#include <stdbool.h>

#define PS2_BASE			0xFF200100

volatile int * ps2_data_reg;
volatile int * ps2_ctr_reg;

bool break_code;  // true if F0 seen
bool extended;     // true if E0 seen
bool shift;        // true if shift is currently pressed


void PS2_init(){
    ps2_data_reg = (volatile int *) PS2_BASE;
    ps2_ctr_reg = (volatile int *) PS2_BASE + 1;

    *ps2_data_reg = 0xFF;   // reset and clear FIFO
    *ps2_ctr_reg  = 0x1;    // enable the PS/2 port (RE bit)

    break_code = false; 
    extended = false;  
    shift = false; 
}

char keycode2ascii(int keycode, bool shift){
    switch (keycode) {
        case 0x1C: return shift ? 'A' : 'a';
        case 0x32: return shift ? 'B' : 'b';
        case 0x21: return shift ? 'C' : 'c';
        case 0x23: return shift ? 'D' : 'd';
        case 0x24: return shift ? 'E' : 'e';
        case 0x2B: return shift ? 'F' : 'f';
        case 0x34: return shift ? 'G' : 'g';
        case 0x33: return shift ? 'H' : 'h';
        case 0x43: return shift ? 'I' : 'i';
        case 0x3B: return shift ? 'J' : 'j';
        case 0x42: return shift ? 'K' : 'k';
        case 0x4B: return shift ? 'L' : 'l';
        case 0x3A: return shift ? 'M' : 'm';
        case 0x31: return shift ? 'N' : 'n';
        case 0x44: return shift ? 'O' : 'o';
        case 0x4D: return shift ? 'P' : 'p';
        case 0x15: return shift ? 'Q' : 'q';
        case 0x2D: return shift ? 'R' : 'r';
        case 0x1B: return shift ? 'S' : 's';
        case 0x2C: return shift ? 'T' : 't';
        case 0x3C: return shift ? 'U' : 'u';
        case 0x2A: return shift ? 'V' : 'v';
        case 0x1D: return shift ? 'W' : 'w';
        case 0x22: return shift ? 'X' : 'x';
        case 0x35: return shift ? 'Y' : 'y';
        case 0x1A: return shift ? 'Z' : 'z';

        case 0x45: return shift ? ')' : '0';
        case 0x16: return shift ? '!' : '1';
        case 0x1E: return shift ? '@' : '2';
        case 0x26: return shift ? '#' : '3';
        case 0x25: return shift ? '$' : '4';
        case 0x2E: return shift ? '%' : '5';
        case 0x36: return shift ? '^' : '6';
        case 0x3D: return shift ? '&' : '7';
        case 0x3E: return shift ? '*' : '8';
        case 0x46: return shift ? '(' : '9';

        case 0x29: return ' ';  // Space
        case 0x5A: return '\n'; // Enter

        default: return 0;
    }
}

char ps2_decoder(int keycode){

    // handle the break and extended codes
    if(keycode == 0xF0) {
        break_code = true;
        return 0;
    }
    else if(keycode == 0xE0) {
        extended = true;
        return 0;
    }

    // change ps2.shift when SHIFT is pressed depending on the break_code
    if(keycode == 0x12 || keycode == 0x59){
        if(break_code) shift = false;
        else shift = true;
        break_code = false;
        extended = false;
        return 0;
    }

    // ignore the scancode during the key release
    if(break_code){
        break_code = false;
        extended = false;
        return 0;
    }

    break_code = false;
    extended = false;
    
    // right now no support for extended keys
    char c = keycode2ascii(keycode, shift);
    return c;   
}

int get_keycode(){
    int RVALID = 0;
	int PS2_data;

    while(1){
        PS2_data = *(ps2_data_reg);          // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000;          // extract the RVALID field
        if(RVALID) 
            return (PS2_data & 0xFF);
    } 
}

char get_char(){
	char c = 0;
	while (c == 0) {
		int keycode = get_keycode();
    	c = ps2_decoder(keycode);
		// printf("%c", c);
	}
    return c;
}

char * get_line(){
    int buffer_size = 20;
    char * str = malloc(buffer_size * sizeof(char));   // buffer for line
    int i = 0;

    while(i < buffer_size - 1){             // leave one char for the terminating character
        char c = get_char();                // get char from PS2 input

        if(c == 0) continue;                // invalid scancode, no support yet, do nothing

        write((char[]) {c,'\0'});           // write c 

        if(c == '\n'){                      // if Enter has been pressed
            str[i] = '\0';                  // add a string termination character
            return str;                     // return
        }
        else{
            str[i] = c;                     // store char in string
            i++;
        }
    }
    str[buffer_size - 1] = '\0';
    return str;
}

// this function gets the first string from a char *
char * get_string(char ** line){
    int buffer_size = 20;
    char * str = malloc(buffer_size * sizeof(char));   // buffer for string
    int i = 0;

    while(**line != '\0'){                 // while line still has chars
        char c = **line;                   // get next char from line
        (*line)++;                         // increment the pointer

        if(c == ' '){                      // if char is a Space
            str[i] = '\0';                 // add a string termination character
            return str;
        }

        else{
            str[i] = c;                     // store char in string
            i++;
        }
    }
    str[i] = '\0';
    return str;
}

/* database.c CONTENT */

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
  int tempo;  
} Score;

// this is the linked list
typedef struct ScoreList {
    struct Score* head; // start of list of all of the scores 
} ScoreList;


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ScoreList is a Linked List with Score as the node
ScoreList scoreList = {NULL};
int score_count;

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
    new_score->tempo = 100;    // arbitrary default value

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
    score_count--;
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

    char* all_names = malloc(score_count*100 * sizeof(char));
    all_names[0] = '\0';

    // not empty list
    while (current != NULL) {
        strcat(all_names, current->name); // adds the name of the current score to the string
        strcat(all_names, "\n"); // for the space between the scores (4 spaces)
        current = current->next;
    }
    return all_names;
}

/* score.c CONTENT */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SW_BASE			0xFF200040
#define KEY_BASE		(volatile int *) 0xFF200050
#define AUDIO_BASE		(volatile int *)0xFF203040
#define PI              3.14159265358979324

const int NOTE_WIDTH = 7;
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

Score* score_input = &(Score){
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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

void draw_score(Score* score);
void play_score(Score* score);

void AUDIO_init();
int isFIFOavailable();
void play_frequency(double frequency, double volume, double duration);

// bool note_drawn = false;

void score(Score* score_input) {
    AUDIO_init();

    pixel_ctrl_ptr = (volatile int *)0xFF203020;

    *(pixel_ctrl_ptr + 1) = (int) &Buffer1;
    swap_buffers_on_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    background(WHITE);

    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); 
    
    int edge_cap;
	
    while (1) {
        unsigned int sw = *SW & 0x3FF;
		
        if (sw & 0x1) {
            edge_cap = *(KEY_BASE + 3);
            // *(KEY_BASE + 3) = 0x3FF;
            if (edge_cap & 0x1) {
                draw_score(score_input);
            }
            if (edge_cap & 0x2) {
                play_score(score_input);
            }
        }
		*(KEY_BASE + 3) = 0x3FF;
    }
}

void draw_score(Score* score){
	// handles drawing the whole score on the page
    // draws the score using different functions for drawing notes
    // draw each note here and call it once in the main function
    background(WHITE);
	
    draw_staff(15, 30);
    draw_time_signature(32, 30);
    // draw_toolbar();
	draw_staff(15, 110);
	draw_staff(15, 190);
	draw_bar_line(HOR_MAX - 15 - 2, 190);
	draw_bar_line(HOR_MAX - 15 - 4, 190);
	
    //swap_buffers_on_vsync();
    //pixel_buffer_start = *(pixel_ctrl_ptr + 1); 
	
    current_hor = 60;
    current_vert = 30 + 27;
    staff_center = 30 + 18;


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
    // take the score and generate frequencies based on notes, play for specified duration
    for (int note_idx = 0; note_idx < 64; note_idx++) { // note_idx for note array
        // read the duration here instead of edge_cap
        Note* current_note = &score->notes[note_idx];
        char duration = current_note->duration;
        char pitch = current_note->note;
        int octave = current_note->octave;
        double frequency = 0.0;
        double dur = 0.0; // name dur because something already named duration
        // also assuming 120bpm right now so 1/120 = 0.008333333333s
        int bpm = 120;
        double secs_per_beat = 60.0 / ((double) bpm);
        
        if (pitch != '\0') { // if note exists
			if (duration == 'w') {
				dur = secs_per_beat * 4;
			}	
            else if (duration == 'h') {
				dur = secs_per_beat * 2;	
			}
			else if (duration == 'q') {
				dur = secs_per_beat;	
			}
			else if (duration == 'e') {
				dur = secs_per_beat / 2;
			}
			else if (duration == 's') {
				dur = secs_per_beat / 4;
			}
				
            // read note here (note and octave together) and get frequency
			if ((pitch == 'C') && (octave == 4)) { // C4
				frequency = 261.63;
			}	
			if ((pitch == 'D') && (octave == 4)) { // D4
				frequency = 293.66;
	    	}
			if ((pitch == 'E') && (octave == 4)) { // E4
				frequency = 329.63;
			}	
			if ((pitch == 'F') && (octave == 4)) { // F4
				frequency = 349.23;
			}
			if ((pitch == 'G') && (octave == 4)) { // G4
                frequency = 392.00;
			}
			if ((pitch == 'A') && (octave == 4)) { // A4
                frequency = 440.00;
			}
			if ((pitch == 'B') && (octave == 4)) { // B4
                frequency = 493.88;
			}
			if ((pitch == 'C') && (octave == 5)) { // C5
                frequency = 523.25;
			}
            if ((pitch == 'D') && (octave == 5)) { // D5
                frequency = 587.33;
	    	}
			if ((pitch == 'E') && (octave == 5)) { // E5
                frequency = 659.25;
			}	
			if ((pitch == 'F') && (octave == 5)) { // F5
                frequency = 698.46;
			}
			if ((pitch == 'G') && (octave == 5)) { // G5
                frequency = 783.99;
			}
			if ((pitch == 'A') && (octave == 5)) { // A5
                frequency = 880.00;
			}
			if ((pitch == 'B') && (octave == 5)) { // B5
                frequency = 987.77;
			}
			if ((pitch == 'C') && (octave == 6)) { // C6
                frequency = 1046.50;
			}
        }
        // end checking note and octave
		
        // generate frequency and feed to audio when audio is ready
        double volume = 0x7FFFFF; // max: 0x7FFFFF; min: 0x800000
        play_frequency(frequency, volume, dur);
        play_frequency(0, volume, 0.1);
	}
}

void AUDIO_init(){
    volatile int * audio_ptr = AUDIO_BASE;
    *(audio_ptr) = 0x8;   // set CW bit to clear/reset the FIFOs first
    *(audio_ptr) = 0x0;   // then clear it to normal
}


int isFIFOavailable(){
    int audio_counters = *(AUDIO_BASE + 1);        //load audio base register
    //RAC = audio_counters & 0xFF;                   
    int WSC = (audio_counters >> 16) & 0xFF;       //extract WSC and RAC value
    int RAC = audio_counters & 0xFF;               //assume left and right FIFO have the same counts

    if(WSC > 0 & RAC > 0) return 1;                //check that there's space in FIFOs
    return 0;                           
}

void play_frequency(double frequency, double amplitude, double duration){
    double t_sample = 125.0 / 1000000.0;
    double period = 1 / frequency;

    double N = period / t_sample;  // this is the number of samples in a period, NOT an integer

    int total_samples = (int)(duration / t_sample);
    int k = 0;                     // written sample count

    // x[n] = A * sin(2PI/N * k)

    while (k < total_samples) {
        if (isFIFOavailable()) {
            double voltage = (double) amplitude * sin(2 * PI * k / N);
            k++;
            *(AUDIO_BASE + 2) = voltage;
            *(AUDIO_BASE + 3) = voltage;
        }
    }
}


/* terminal.c CONTENT */

#include <string.h>

char* help_menu = "\'new <name>\'\n'open <name>\'\n\'delete <name>\'\n\'list\'\n\'clear\'\n";

int terminal(){
    VGA_init();
    PS2_init();
    background(BLACK);

    while(1){
        write(">> ");
        char * line = get_line();
        char * command = get_string(&line);

        const char * str_new = "new";
        const char * str_open = "open";
        const char * str_delete = "delete";
        const char * str_list = "list";
        const char * str_help = "help";
        const char * str_clear = "clear";


        if(strcmp(command, str_new) == 0){
            char* name = get_string(&line); 
            if(exists(name)) {
                write("Name already exists.\n");
                continue;
            }
            struct Score* scr = add(name);
            write("New score \'");
            write(name);
            write("\' added.\n");
            // open score
            score(scr);
            // write("Pretend the score opened!\n");
        }

        else if(strcmp(command, str_open) == 0){
            char* name = get_string(&line);
            if(!exists(name)) {
                write("\'");
                write(name);
                write("\' doesn't exist.\n");
                continue;
            }
            struct Score* scr = find(name);
            write("Opening \'");
            write(name);
            write("\'...\n");
            // open score
            score(scr);
            write("Pretend the score opened!\n");
        }

        else if(strcmp(command, str_delete) == 0){
            char* name = get_string(&line);
            if(!exists(name)) {
                write("\'");
                write(name);
                write("\' doesn't exist.\n");
                continue;
            }
            delete(name);
            write("\'");
            write(name);
            write("\' deleted.\n");
        }
        
        else if(strcmp(command, str_list) == 0){
            char* list = get_scores();
            write(list);
        }

        else if(strcmp(command, str_help) == 0){
            write(help_menu);
        }

        else if(strcmp(command, str_clear) == 0){
            background(BLACK);
            swap_buffers_on_vsync();
            pixel_buffer_start = *(pixel_ctrl_ptr + 1);       // change to back buffer
            background(BLACK);
            CURSOR_X = CURSOR_X_DEFAULT;
            CURSOR_Y = CURSOR_Y_DEFAULT;
        }

        else{
            write("Invalid command.\n");
        }

    }
}

int main(){
    terminal();
}