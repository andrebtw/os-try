#ifndef VGATEXT_H
#define VGATEXT_H

#include "stdint.h"

// VGA mode 3 video buffer
#define VGA_VIDEO_BUFFER_LOCATION 0xB8000

// VGA Colors
#define VGA_BLACK_COLOR 0
#define VGA_BLUE_COLOR 1
#define VGA_GREEN_COLOR 2
#define VGA_CYAN_COLOR 3
#define VGA_RED_COLOR 4
#define VGA_MAGENTA_COLOR 5
#define VGA_BROWN_COLOR 6
#define VGA_LIGHTGRAY_COLOR 7
#define VGA_DARKGRAY_COLOR 8
#define VGA_LIGHTBLUE_COLOR 9
#define VGA_LIGHTGREEN_COLOR 10
#define VGA_LIGHTCYAN_COLOR 11
#define VGA_LIGHTRED_COLOR 12
#define VGA_LIGHTMAGENTA_COLOR 13
#define VGA_YELLOW_COLOR 14
#define VGA_WHITE_COLOR 15

// Buffer pos
#define VGA_COLOR_BUFFER 1
#define VGA_CHARACTER_BUFFER 0

// Screen length
#define VGA_HEIGHT 80
#define VGA_LENGTH 25


// Clears all the screen with black
void    VGA_clear_screen(void);

// Printing
void    VGA_print_char(uint8 c, uint16 x, uint16 y, uint16 background_color, uint16 font_color);
void    VGA_print_str(uint8 *str, uint16 x, uint16 y, uint16 background_color, uint16 font_color);
void    VGA_print_hex_8(uint8 byte, uint16 x, uint16 y, uint16 background_color, uint16 font_color);
void    VGA_set_cursor(uint8 x, uint8 y);
#endif