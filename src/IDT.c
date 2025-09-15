#include "stdlib.h"
#include "IDT.h"
#include "vga_text.h"

extern void isr0(void);

IDT_descriptor  idt_p;
IDT_Entry32     idt_entries[256];

static void    IDT_Set(IDT_Entry32 *idt_entry, uint32 handler)
{
    idt_entry->address_low = handler & 0x0000FFFF;
    idt_entry->selector = 0x08;
    idt_entry->zero = 0x00;
    idt_entry->type = 0x8E;
    idt_entry->address_high = (handler & 0xFFFF0000) >> 16;
}

uint8   IDT_Init(void)
{
    idt_p.limit = (sizeof(IDT_Entry32) * 256) - 1;
    idt_p.base = (uint32)&idt_entries;
    for (size_t i = 0; i < 256; i++)
    {
        IDT_Set(&idt_entries[i], (uint32)isr0);
    }

    asm volatile ("lidt %0" : : "m"(idt_p));
    return 0;
}

void    handler(void)
{
    VGA_print_str("DIVIDED BY ZERO", 10, 10, VGA_BLACK_COLOR, VGA_RED_COLOR);
    for (;;);
}
