#ifndef IO_H
#define IO_H

#include "stdint.h"

void outb(uint16 port, uint8 value);
uint8 inb(uint16 port);

#endif