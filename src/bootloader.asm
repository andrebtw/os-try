[BITS 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 


; put the stack in a safe spot
mov sp, 0x8000
mov bp, sp


; save booting drive number, BIOS puts it by default on the dl
mov [BOOT_DRIVE], dl

mov bx, bootloader_starting_str
call print_str

mov dl, [BOOT_DRIVE]
mov dh, 15
mov bx, KERNEL_OFFSET
call load_disk


mov ax, 0x2401
int 0x15
call enable_protected_mode


call KERNEL_OFFSET ; jump to the address of the loaded kernel


;; dl BOOT DRIVER ; dh NB OF SECTORS ; bx ADDRESS BUFFER
load_disk:
    push dx
    mov ah, 0x02 ; read sector function

    mov al, dh ; nb of sectors to read
    mov ch, 0x0 ; cylinder number, first to read begin of disk
    mov cl, 0x02 ; starting to read at sector 2 bcs 1 is the 512 of this bootloader
    mov dh, 0x0 ; head number to be the first
    ;; i dont dl bcs we already set it before calling this function
    ;; this will read the first set 'dh' sectors to read
    ;; the location will be on the address 'bx' that i set before
    ;; with the offset of 'es' if i want one

    int 0x13 ;; interrupt call to read disk
    pop dx

    ret

enable_protected_mode:
    cli ; disable CPU interrupts
    lgdt [gdt_descriptor] ; load GDT 

    ; cr0 special register that the first bit must be set to 1 so the CPU understands the switch to 32 bit
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:start_protected_mode


[BITS 32]
start_protected_mode:
    mov ax, DATA_SEG
    ; pointing all segments to data segment defined
	mov ds, ax 
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; stack at safe place
    mov esp, ebp 

	ret




[BITS 16]
gdt_start:
    ; null descriptor needed before gdt section
    dd 0x00000000
    dd 0x00000000

    ; gdt segment descriptor for code
    ; gdt segment is made of 64 bits

    ; the base address bits part will always be at 0
    ; because it starts at the beginning of the memory (for flat memory model)

    ; (first 32 bytes)
    ; 0->15 : segment limit (low part of bytes)
    ; 16->31 : base address (low part)

    ; (last 32 bytes)
    ; 0->7 : base address (middle part)


    ; 8->15 : "Access Byte" segment read, write, execute rights
    ; bit 7 : is the segment present in the memory (0: no ; 1: yes)
    ; bit 6-5 : privilege (0: highest ; 1: high ; 2: medium ; 3: lowest)
    ; bit 4 : Descriptor type (1: code/data segment ; 0: system segment)
    ; bit 3 : executable (1: yes ; 0: no)

    ; bit 2 (if bit 3 == executable) : 
            ; Conforming (0: executable only at the same privilege level ; 1: can execute at other privilege)
    ;       (if bit 3 == data) :
            ; Data grows up in memory (1: yes ; 0: no)

    ; bit 1 : (if bit 3 == executable) :
            ; Perms (0: only executable, 1: readable and executable)
            ; (if bit 3 == data) : 
            ; Perms (0: only readable, 1: read and write)

    ; bit 0 : Accessed (0: no ; 1 : yes)


    ; 16->23 : flags and segment limit (high part)
    ; bit 7 : granularity (0: limit is in bytes ; 1: limit is in 4 KB pages)
    ; bit 6 : size of segment (0: 16 bit; 1: 32 bit)
    ; bit 5 : always 0 
    ; bit 4 : AVL (the os can read this bit value, whatever)
    ; bit 3->0 : segment limit (high part)


    ; 24->31 : base address (high part)

gdt_code:
    ;; first 32 bits
    dw 0xffff ; base address low
    dw 0x0000 ; segment limit low

    ;; last 32 bits
    db 0x00 ; base address mid
    ;; access byte
    db 10011010b ; access byte (set exec seg, exec n read perms, privilege 0)
    db 11001111b ; flags and segment limit high
    db 0x00 ; base address high

gdt_data:
    ;; first 32 bits
    dw 0xffff ; base address low
    dw 0x0000 ; segment limit low

    ;; last 32 bits
    db 0x00 ; base address mid
    ;; access byte
    db 10010010b ; access byte (set data seg, read n write perms, privilege 0)
    db 11001111b ; flags and segment limit high
    db 0x00 ; base address high

gdt_end: ; label to calculate the GDT size for the GDT descriptor

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of GDT
    ; of the true size
    dd gdt_start ; address of GDT start

;; Print disk error
print_disk_error_msg:
    mov bx, disk_error_str
    call print_str
    mov bx, ax
    call print_hex
    mov bx, dx
    call print_hex
    jmp $


;; A function that prints a string using a jmp loop until a 0 value byte is found ;; 
print_str:
    pusha
    mov ah, 0x0e
    jmp begin_loop_print_str
 
begin_loop_print_str:
    cmp byte [bx], 0
    jne write_char_print_str
    popa
    ret

write_char_print_str:
    mov al, [bx]
    int 0x10
    add bx, 1
    jmp begin_loop_print_str


;; Function that prints a 4 byte number in hex (Made this just to get used to assembly) ;;
print_hex:
    pusha
    mov cl, bh
    cmp cl, 0x00FF
    mov ch, 0

print_hex_loop:
    cmp ch, 0
    je step1_print_hex

    mov cl, bh

    cmp ch, 1
    je step2_print_hex

    mov cl, dl
    
    cmp ch, 2
    je step1_print_hex

    mov cl, bl

    cmp ch, 3
    je step2_print_hex
    
    popa
    ret

step1_print_hex:
    and cl, 0xF0
    shr cl, 4
    cmp cl, 10
    jl less_than_ten_print_hex
    jge ten_or_more_print_hex 

step2_print_hex:    
    and cl, 0x0F
    cmp cl, 10
    jl less_than_ten_print_hex
    jge ten_or_more_print_hex
    
less_than_ten_print_hex:
    add cl, '0'
    mov ah, 0x0e
    mov al, cl
    int 0x10
    add ch, 1
    jmp print_hex_loop
    
ten_or_more_print_hex:
    add cl, 87
    mov ah, 0x0e
    mov al, cl
    int 0x10
    add ch, 1
    jmp print_hex_loop


;; Strings ;;
bootloader_starting_str:
    db 'Bootloader starting...', 0

protected_mode_str:
    db 'Started in 32 bit protected mode', 0

disk_error_str:
    db 'There was some error trying to read the disk :(', 0

kernel_loaded_str:
    db 'KERNEL LOADED', 0

;; Variables ;;
BOOT_DRIVE db 0

;; Constants ;;
;; Address of each GDT segment
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


times 510-($-$$) db 0
dw 0xaa55

