[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_str_pm:
	; prints a null-terminated string from address given in ebx
	pusha
	
	mov edx, VIDEO_MEMORY
	print_str_pm_loop:
		mov al, [ebx]
		mov ah, WHITE_ON_BLACK
		cmp al, 0x0
		je print_str_pm_loop_exit 
		mov [edx], ax
		inc ebx
		add edx, 2
		jmp print_str_pm_loop
		print_str_pm_loop_exit:

	popa
	ret

clear_screen_pm:
	pusha
	
	mov edx, 0
	mov ah, WHITE_ON_BLACK
	clear_screen_pm_loop:
		cmp edx, 4000
		je clear_screen_pm_loop_exit 
		mov al, ' '
		mov [VIDEO_MEMORY + edx], ax
		add edx, 2
		jmp clear_screen_pm_loop
		clear_screen_pm_loop_exit:

	popa
	ret