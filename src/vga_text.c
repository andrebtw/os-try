#include "vga_text.h"
#include "stdint.h"

/* 0xB8000 is the start of the memory address for VGA text
80x25 resolution, each character is 16 bit
8 higher bit for the color and 8 lower bits for the character
background | foreground | character
*/

void VGA_clear_screen(void)
{
    volatile uint8 *video_buffer = (volatile uint8 *)VGA_VIDEO_BUFFER_LOCATION;

    for (uint16 i = 0; i < 2000; i++)
    {
        video_buffer[VGA_CHARACTER_BUFFER] = ' ';
        video_buffer[VGA_COLOR_BUFFER] = 0x00;
        video_buffer = video_buffer + 2;
    }
}

void VGA_print_char(uint8 c, uint16 x, uint16 y, uint16 background_color, uint16 font_color)
{
    volatile uint8 *video_buffer = (volatile uint8 *)VGA_VIDEO_BUFFER_LOCATION;

    uint16 buffer_pos = (y * 160) + (x * 2);
    uint8 color_byte = font_color | background_color << 4;

    video_buffer[VGA_CHARACTER_BUFFER + buffer_pos] = c;
    video_buffer[VGA_COLOR_BUFFER + buffer_pos] = color_byte;
}

void VGA_print_str(uint8 *str, uint16 x, uint16 y, uint16 background_color, uint16 font_color)
{
    if (!str)
        return ;

    for (uint64 i = 0; str[i] != '\0'; i++)
        VGA_print_char(str[i], x + i, y, background_color, font_color);
}
