[BITS 32]

extern isr0_devide_error
extern isr14_page_fault

global isr0
isr0:
    cli ;disable interrupts
    pushad

    call isr0_devide_error
    
    sti ;enable interrupts
    popad
    iret ;ret

global isr14
isr14:
    cli
    pushad

    call isr14_page_fault

    sti
    popad
    iret