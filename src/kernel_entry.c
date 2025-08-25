#include "vga_text.h"
#include "stdint.h"
#include "io.h"
#include "keyboard.h"
#include "stdlib.h"
#include "ATA.h"

void main(void)
{
    outb(0x64, 0xAE); // enables PS/2 port 
    VGA_fill_screen(VGA_BLACK_COLOR);
    // VGA_print_str("Discovering disks...", 0, 0, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    // VGA_set_cursor(strlen("Discovering disks...") + 1, 0);

    VGA_print_str("C code loaded.", 0, 0, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    VGA_set_cursor(strlen("C code loaded.") + 1, 0);
    char c;
    while (1)
    {
        c = read_char();
        uint8 status = inb(ATA_STATUS_PORT);
        VGA_print_hex_8(status, 0, 4, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        for (;;)
        {
        }
    };
}
