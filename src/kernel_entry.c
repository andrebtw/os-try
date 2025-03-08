#include "kernel.h"

void main(void)
{
    VGA_clear_screen();
    VGA_print_char('t', 1, 1, VGA_BLACK_COLOR, VGA_LIGHTCYAN_COLOR);
    VGA_print_str("TEXT WORKS!!!! :)", 70, 10, VGA_BLACK_COLOR, VGA_LIGHTCYAN_COLOR);
    while (1);
}
