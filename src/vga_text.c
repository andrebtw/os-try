#include "vga_text.h"
#include "stdint.h"
#include "io.h"

/* 0xB8000 is the start of the memory address for VGA text
80x25 resolution, each character is 16 bit
8 higher bit for the color and 8 lower bits for the character
background | foreground | character
*/

void VGA_fill_screen(uint8 color)
{
    volatile uint8 *video_buffer = (volatile uint8 *)VGA_VIDEO_BUFFER_LOCATION;

    for (uint16 i = 0; i < 2000; i++)
    {
        video_buffer[VGA_CHARACTER_BUFFER] = ' ';
        video_buffer[VGA_COLOR_BUFFER] = (color << 4);
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

static uint8 convert_to_ascii(uint8 byte)
{
    if (byte <= 9)
        return byte + '0';
    byte = byte - 10;
    return byte + 'A';
}


void VGA_print_hex_8(uint8 byte, uint16 x, uint16 y, uint16 background_color, uint16 font_color)
{
    uint8 byte_lowpart = byte & 0x0F;
    uint8 byte_highpart = (byte & 0xF0) >> 4;

    VGA_print_str("0x", x, y, background_color, font_color);
    byte_lowpart = convert_to_ascii(byte_lowpart);
    byte_highpart = convert_to_ascii(byte_highpart);

    VGA_print_char(byte_highpart, x+2, y, background_color, font_color);
    VGA_print_char(byte_lowpart, x+3, y, background_color, font_color);
}

void    VGA_set_cursor(uint8 x, uint8 y)
{
    uint16 cursor_pos = x + (y * VGA_LENGTH);
    outb(0x3D4, 0x0E); // port 0x3d4 (address register) will get higher part of the cursor pos
    outb(0x3D5, (cursor_pos & 0x00FF) >> 8); // gets the left 8 bits of the 16 bit and writes on the address register
    outb(0x3D4, 0x0F); // port 0x3d4 (address register) will get lower part of the cursor pos
    outb(0x3D5, (cursor_pos & 0x00FF)); // right side of the 16 bit on the data port 
}
