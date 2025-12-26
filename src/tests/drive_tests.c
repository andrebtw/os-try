#include "../../include/stdint.h"
#include "../../include/ATA.h"
#include "../../include/vga_text.h"

void drive_test()
{
    uint8 buffer[512];
    uint8 err_code = 0;
    uint8 b[512];
    uint32 j = 0;
    uint32 k = 0;
    int i = 0;
    
    j = 0;
    
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


    if (write_sectors(15, 1, words, 1))
        return ;
    uint8 buffer2[512];
    
    err_code = read_sectors(15, 1, buffer2);
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
}