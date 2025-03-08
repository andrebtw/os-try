#ifndef VGATEXT_H
#define VGATEXT_H

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


// Clears all the screen with black
void VGA_clear_screen(void);

// Printing
void VGA_print_char(unsigned char c, unsigned short x, unsigned short y, unsigned short background_color, unsigned short font_color);
void VGA_print_str(unsigned char *str, unsigned short x, unsigned short y, unsigned short background_color, unsigned short font_color);

#endif