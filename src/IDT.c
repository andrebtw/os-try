#include "../include/stdlib.h"
#include "../include/interrupts.h"
#include "../include/vga_text.h"

extern char *last_err;

extern void isr0(void);
extern void isr14(void);

IDT_descriptor  idt_p;
IDT_Entry32     idt_entries[256];

void default_handler(void)
{
    VGA_print_str("Default handler called.", 0, 0, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
    for (;;);
}

void isr0_devide_error(void)
{
    VGA_print_str("DIVIDED BY ZERO!", 0, VGA_HEIGHT - 1, VGA_BLACK_COLOR, VGA_RED_COLOR);
    for (;;);
}

void isr14_page_fault(void)
{
    VGA_print_str("PAGE FAULT!", 0, 0, VGA_BLACK_COLOR, VGA_RED_COLOR);
    for (;;);
}

static void IDT_Set(IDT_Entry32 *idt_entry, uint32 handler)
{
    idt_entry->address_low = handler & 0x0000FFFF;
    idt_entry->selector = 0x08;
    idt_entry->zero = 0x00;
    idt_entry->type = 0x8E;
    idt_entry->address_high = (handler & 0xFFFF0000) >> 16;
}

uint8 IDT_Init(void)
{
    idt_p.limit = (sizeof(IDT_Entry32) * 256) - 1;
    idt_p.base = (uint32)&idt_entries;

    /* Set default handler for now*/
    for (size_t i = 0; i < 256; i++)
    {
        IDT_Set(&idt_entries[i], (uint32)default_handler);
    }
    IDT_Set(&idt_entries[0], (uint32)isr0);
    IDT_Set(&idt_entries[14], (uint32)isr14);
    asm volatile ("lidt %0" : : "m"(idt_p));
    return 0;
}
