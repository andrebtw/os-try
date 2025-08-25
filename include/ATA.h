#ifndef ATA_H
#define ATA_H

// Data register : read:write pio data bytes
#define ATA_BASE 0x1F0

#define ATA_DATA_PORT ATA_BASE
#define ATA_ERROR_PORT ATA_BASE + 1
#define ATA_FEATURE_PORT ATA_BASE + 1
#define ATA_SECTORS_COUNT_PORT ATA_BASE + 2	
#define ATA_LBA_LOW_PORT ATA_BASE + 3
#define ATA_LBA_MID_PORT ATA_BASE + 4
#define ATA_LBA_HIGH_PORT ATA_BASE + 5
#define ATA_DRIVE_PORT ATA_BASE + 6
#define ATA_HEAD_PORT ATA_BASE + 6
#define ATA_STATUS_PORT ATA_BASE + 7
#define ATA_CMD_PORT ATA_BASE + 7

#endif