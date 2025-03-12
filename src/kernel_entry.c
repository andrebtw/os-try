#include "vga_text.h"
#include "stdint.h"

void main(void)
{
    VGA_clear_screen();
    VGA_print_str("OS TEST! :)", 0, 0, VGA_BLACK_COLOR, VGA_LIGHTCYAN_COLOR);
    while (1);
}
