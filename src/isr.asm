[BITS 32]

extern handler

global isr0

isr0:
    cli ;disable interrupts
    call handler
    
    sti ;enable interrupts
    
    iret ;ret