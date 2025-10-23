#include "vga_text.h"
#include "stdint.h"
#include "io.h"
#include "keyboard.h"
#include "stdlib.h"
#include "ATA.h"
#include "interrupts.h"

char last_err[50];

void kmain(void)
{
    IDT_Init();

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
    uint8 err_code = 0;
    uint8 b[512];
    uint32 j = 0;
    uint32 k = 0;
    int i = 0;
    
    j = 0;
    
    drive_init();

    err_code = read_sectors(5, 1, buffer);
    if (err_code == ERRK_BSY)
    {
        VGA_print_str("BSY timeoutd", 0, 15, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
        for (;;);
    }
    else if (err_code == ERRK_DRQ)
    {
        VGA_print_str("DRQ timeoutd", 0, 15, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
        for (;;);
    }

    for (uint32 i = 0; i < 12; i++)
    {
        if (j >= 75)
        {
            j = 0;
            k++;
        }
        VGA_print_hex_byte(buffer[0 + i], j, k, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        j = j + 5;
    }

    uint16 words[256];
    for (size_t i = 0; i < 256; i++)
    {
        words[i] = i;
    }


    if (write_sectors(5, 1, words, 1))
        return ;
    uint8 buffer2[512];
    
    err_code = read_sectors(5, 1, buffer2);
    if (err_code == ERRK_BSY)
    {
        VGA_print_str("BSY timeoutd", 0, 15, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
        for (;;);
    }
    else if (err_code == ERRK_DRQ)
    {
        VGA_print_str("DRQ timeoutd", 0, 15, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
        for (;;);
    }
    k=k+1;
    j = 0;
    for (uint32 i = 0; i < 12; i++)
    {
        if (j >= 75)
        {
            j = 0;
            k++;
        }
        VGA_print_hex_byte(buffer2[0 + i], j, k, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
        j = j + 5;
    }

    
    
    // VGA_print_hex_byte(buffer[0], 0, 7, VGA_BLACK_COLOR, VGA_WHITE_COLOR);
    
    int bfioezj = 8 / 0;

    VGA_print_str("THIS EXECUTES", 0, 8, VGA_BLACK_COLOR, VGA_GREEN_COLOR);


    for (;;);
}
