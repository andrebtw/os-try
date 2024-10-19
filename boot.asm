[org 0x7c00]



mov bx, my_string
call print_str

mov dx, 0xceb6
call print_hex

loop:
	jmp loop




;; PRINT STR ;; 
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


;; PRINT HEX ;;
print_hex:
	pusha
	mov cl, dh
	cmp cl, 0x00FF
	mov ch, 0

print_hex_loop:
	cmp ch, 0
	je step1_print_hex

	mov cl, dh

	cmp ch, 1
	je step2_print_hex

	mov cl, dl
	
	cmp ch, 2
	je step1_print_hex

	mov cl, dl

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




;; VARIABLES ;;
my_string:
	db 'OS Started...', 0


times 510-($-$$) db 0
dw 0xaa55
