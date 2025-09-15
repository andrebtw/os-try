#include "ATA.h"
#include "io.h"
#include "vga_text.h"

int8    check_bsy(void)
{
    uint32 timeout = 0;
    while (inb(ATA_STATUS_PORT) & 0b10000000 && timeout < 100000)
    {
        timeout++;
    }
    if (timeout >= 100000)
        return 1;
    return 0;
}

int8    check_rdy(void)
{
    uint32 timeout = 0;
    while (!(inb(ATA_STATUS_PORT) & 0b00001000) && timeout < 100000)
    {
        timeout++;
    }
    if (timeout >= 100000)
        return 1;
    return 0;
}

void    drive_init(void)
{
    uint16 buffer[256];

    uint8 status = inb(ATA_STATUS_PORT);

    // Wait for one of BSY or DRQ to be at 0
    while (status & 0b10000000 && status & 0x00001000)
        status = inb(ATA_STATUS_PORT);

    outb(ATA_SECTORS_COUNT_PORT, 0);
    outb(ATA_LBA_LOW_PORT, 0);
    outb(ATA_LBA_MID_PORT, 0);
    outb(ATA_LBA_HIGH_PORT, 0);
    outb(ATA_DRIVE_HEAD_PORT, 0b11100000);

    // Read command
    outb(ATA_CMD_PORT, ATA_READ_CMD);

    // Wait while BSY is 1
    while ((inb(ATA_STATUS_PORT) & 0b10000000));

    // Wait until DRQ is set to 0
    while (!(inb(ATA_STATUS_PORT) & 0b00001000));

    for (uint64 i = 0; i < 256; i++)
        buffer[i] = inw(ATA_DATA_PORT);
}

/* THIS DOESNT WORK ALL THE TIMES */
void    read_sectors(uint32 lba, uint32 sector_count, uint8 *buffer)
{
    uint64 buffer_index = 0;
    uint16 data;

    uint8 status = inb(ATA_STATUS_PORT);

    outb(ATA_SECTORS_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, lba >> 8);
    outb(ATA_LBA_HIGH_PORT, lba >> 16);
    outb(ATA_DRIVE_HEAD_PORT, (0b11100000 | (lba >> 24)));

    // wait 400ns
    for (uint64 i = 0; i < 15; i++)
        status = inb(ATA_STATUS_PORT);

    check_bsy();
    check_rdy();
    
    // Read command
    outb(ATA_CMD_PORT, ATA_READ_CMD);

    // Read words with inw data port
    for (uint64 i = 0; i < 256 * sector_count; i++)
    {
        data = inw(ATA_DATA_PORT);
        buffer[i * 2 + buffer_index] = (uint8)(data & 0xFF);
        buffer[i * 2 + 1 + buffer_index] = (uint8)(data >> 8);
    }
}

/* To finish */
void    write_sectors(uint32 lba, uint32 sector_count, uint16 *words, uint64 len)
{
    uint64 buffer_index = 0;
    uint16 data;

    uint8 status = inb(ATA_STATUS_PORT);

    // Wait for one of BSY or DRQ to be at 0
    while (status & 0b10000000 || status & 0x00001000)
        status = inb(ATA_STATUS_PORT);
    
    outb(ATA_SECTORS_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, lba >> 8);
    outb(ATA_LBA_HIGH_PORT, lba >> 16);
    outb(ATA_DRIVE_HEAD_PORT, (0b11100000 | (lba >> 24)));

    // wait 400ns
    for (uint64 i = 0; i < 15; i++)
        status = inb(ATA_STATUS_PORT);

    // Write command
    outb(ATA_CMD_PORT, ATA_WRITE_CMD);

    // Wait while BSY is 1
    while ((inb(ATA_STATUS_PORT) & 0b10000000));

    // Wait until DRQ is set to 0
    while (!(inb(ATA_STATUS_PORT) & 0b00001000));

    // Write words with outw data port
    for (uint64 i = 0; i < 256; i++)
    {
        outw(ATA_DATA_PORT, 0x6969);
        asm volatile (".byte 0xEB, 0x00" ::: "memory");   // Tiny delay using jmp opcode
    }

    outb(ATA_CMD_PORT, ATA_FLUSH_CMD);
}

