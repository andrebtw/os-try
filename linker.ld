KERNEL_JUMP = 0x1000;
PAGE_SIZE = 0x1000; 

ENTRY(kmain)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    . = KERNEL_JUMP;

    .text :
    {
        . = ALIGN(PAGE_SIZE);
        *(.text)
        *(.rodata)
    }

    .data :
    {
        . = ALIGN(PAGE_SIZE);
        *(.data)
    }

    .bss :
    {
        . = ALIGN(PAGE_SIZE);
        *(.bss)
    }
}
