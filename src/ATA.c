#include "ATA.h"
#include "io.h"
#include "vga_text.h"

void    read_sectors(uint32 lba, uint32 sector_count, uint8 *buffer, int *i)
{
    uint64 buffer_index = 0;
    uint16 data;

    uint8 status = inb(ATA_STATUS_PORT);

    // Wait for one of BSY or DRQ to be at 0
    while (status & 0b10000000 && status & 0x00001000)
        status = inb(ATA_STATUS_PORT);

    outb(ATA_SECTORS_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, lba >> 8);
    outb(ATA_LBA_HIGH_PORT, lba >> 16);
    outb(ATA_DRIVE_HEAD_PORT, (0b11100000 | (lba >> 24)));

    // wait 400ns
    for (uint64 i = 0; i < 15; i++)
        status = inb(ATA_STATUS_PORT);

    // Read command
    outb(ATA_CMD_PORT, ATA_READ_CMD);

    // Wait while BSY is 1
    while ((inb(ATA_STATUS_PORT) & 0b10000000));

    // Wait until DRQ is set to 0
    while (!(inb(ATA_STATUS_PORT) & 0b00001000));

    // Read words with inw data port
    for (uint64 i = 0; i < 256; i++)
    {
        data = inw(ATA_DATA_PORT);
        buffer[i * 2 + buffer_index] = (uint8)(data & 0xFF);
        buffer[i * 2 + 1 + buffer_index] = (uint8)(data >> 8);
    }
}
