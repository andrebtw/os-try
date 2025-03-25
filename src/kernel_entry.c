#include "vga_text.h"
#include "stdint.h"
#include "io.h"
#include "keyboard.h"

void main(void)
{
    outb(0x64, 0xAE); // enables PS/2 port 
    VGA_fill_screen(VGA_LIGHTBLUE_COLOR);
    VGA_print_str("OS TEST! :)", 0, 0, VGA_LIGHTBLUE_COLOR, VGA_BLACK_COLOR);
    VGA_set_cursor(10, 7);

    char c;
    while (1)
    {
        c = read_char();
        VGA_print_hex_8(c, 40, 10, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        VGA_print_hex_8(c, 40, 10, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    };
}
