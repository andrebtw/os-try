#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "stdlib.h"

extern const uint32 GLOBAL_CS_OFFSET;
extern const uint32 GLOBAL_DS_OFFSET;

#define IDT_BASE 0x0800

typedef struct __attribute__((packed)) s_idtp
{
    uint16 limit; // size of idt
    uint32 base; // idt address
} IDT_descriptor;

typedef struct __attribute__((packed)) s_idt_entry32
{
    uint16  address_low; //address of handler
    uint16  selector;
    uint8   zero;
    uint8   type;
    uint16  address_high; // address of handler
} IDT_Entry32;

uint8 IDT_Init(void);

#endif