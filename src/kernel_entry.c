#include "vga_text.h"
#include "stdint.h"
#include "io.h"
#include "keyboard.h"
#include "stdlib.h"
#include "ATA.h"
#include "interrupts.h"

void kmain(void)
{
    
    outb(0x64, 0xAE); // enables PS/2 port 
    VGA_fill_screen(VGA_BLACK_COLOR);
    // VGA_print_str("Discovering disks...", 0, 0, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    // VGA_set_cursor(strlen("Discovering disks...") + 1, 0);

    // VGA_print_str("C code loaded.", 0, 0, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    // VGA_set_cursor(strlen("C code loaded.") + 1, 0);
    // char c;

    outb(ATA_CMD_PORT, ATA_IDENTIFY_CMD);

    // VGA_print_binary_byte(status, 0, 5, VGA_BLACK_COLOR, VGA_WHITE_COLOR);

    uint8 buffer[512];

    uint8 b[512];
    uint32 j = 0;
    uint32 k = 0;
    int i = 0;
    
    drive_init();
    for (uint32 i = 0; i < 12; i++)
    {
        if (j >= 75)
        {
            j = 0;
            k++;
        }
        VGA_print_hex_byte(buffer[500 + i], j, k, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        j = j + 5;
    }
    k++;
    k++;
    j = 0;
    uint16 words[256];
    // write_sectors(0, 1, words, 2);
    read_sectors(0, 1, buffer);
    for (uint32 i = 0; i < 12; i++)
    {
        if (j >= 75)
        {
            j = 0;
            k++;
        }
        VGA_print_hex_byte(buffer[500 + i], j, k, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        j = j + 5;
    }
    IDT_Init();
    // VGA_print_hex_byte(buffer[0], 0, 7, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    
    int bfioezj = 8 / 0;

    VGA_print_str("THIS EXECUTES", 0, 8, VGA_BLACK_COLOR, VGA_GREEN_COLOR);

    
    for (;;);

}
