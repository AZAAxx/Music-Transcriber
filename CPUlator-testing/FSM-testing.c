/*
THE FOLLOWING IS JUST THE ADAFRUIT FILES, VGA, AND DRAWFONT.C FILE ALL PUT INTO THE FILE
*/



// Font structures for newer Adafruit_GFX (1.1 and later).
// Example fonts are included in 'Fonts' directory.
// To use a font in your Arduino sketch, #include the corresponding .h
// file and pass address of GFXfont struct to setFont().  Pass NULL to
// revert to 'classic' fixed-space bitmap font.

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





/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


 /* 
 WARNING: This file has been altered to fix some errors, refer to the 
 Adafruit Github repository for the original version. 
 */


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


int CURSOR_X;                                // arbitrary values for now
int CURSOR_Y;

int CURSOR_X_DEFAULT;                      
int CURSOR_Y_DEFAULT;



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

    CURSOR_Y_DEFAULT = 20;                             // arbitrary values for now
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

#include <stdlib.h>
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

Score test_score = {"TestScore", {{'A', 4, 'w'},  {'G', 4, 'h'}}, NULL, 120}; 

// ScoreList is a Linked List with Score as the node
ScoreList scoreList = {&test_score};
int score_count = 0;

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
            //score(scr);
            write("Pretend the score opened!\n");
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
            //score(scr);
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