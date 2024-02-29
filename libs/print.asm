print_new_line:
	pusha
	mov al, 0xd 
	call print_char
	mov al, 0xa 
	call print_char
	popa
	ret

clear_screen:
	pusha
	
	mov bx, 0x0
	mov al, 0x0
	clear_screen_loop:
	call print_char
	inc bx
	cmp bx, 4000
	jne clear_screen_loop

	popa
	ret

print_str:
	; prints null-terminated string from address stored in bx
	pusha
	
	print_loop:
	mov al, byte [bx]
	call print_char
	inc bx
	cmp byte [bx], 0x0
	jne print_loop
	
	popa
	ret

print_char:
	; prints char from al register
	pusha
	mov ah, 0x0e
	int 0x10
	popa
	ret