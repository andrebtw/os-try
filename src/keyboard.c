#include "keyboard.h"
#include "io.h"
#include "debug.h"
#include "stdlib/stdlib.h"


uint8    read_char(void)
{
    uint8 character;
    uint8 status;

    status = inb(0x64);
    while ((status & 0x01) == 0)
    {
        status = inb(0x64);
    }
    character = inb(0x60);
    return character;
}
