#include "vga_text.h"

/* 0xB8000 is the start of the memory address for VGA text
80x25 resolution, each character is 16 bit
8 higher bit for the color and 8 lower bits for the character
background | foreground | character
*/

void VGA_clear_screen(void)
{
    volatile unsigned char *video_buffer = (volatile unsigned char *)VGA_VIDEO_BUFFER_LOCATION;

    for (unsigned short i = 0; i < 2000; i++)
    {
        video_buffer[VGA_CHARACTER_BUFFER] = ' ';
        video_buffer[VGA_COLOR_BUFFER] = 0x00;
        video_buffer = video_buffer + 2;
    }
}

void VGA_print_char(unsigned char c, unsigned short x, unsigned short y, unsigned short background_color, unsigned short font_color)
{
    volatile unsigned char *video_buffer = (volatile unsigned char *)VGA_VIDEO_BUFFER_LOCATION;

    unsigned short buffer_pos = (y * 160) + (x * 2);
    unsigned char color_byte = font_color | background_color << 4;

    video_buffer[VGA_CHARACTER_BUFFER + buffer_pos] = c;
    video_buffer[VGA_COLOR_BUFFER + buffer_pos] = color_byte;
}

void VGA_print_str(unsigned char *str, unsigned short x, unsigned short y, unsigned short background_color, unsigned short font_color)
{
    if (!str)
        return ;

    for (unsigned long long i = 0; str[i] != '\0'; i++)
        VGA_print_char(str[i], x + i, y, background_color, font_color);
}
