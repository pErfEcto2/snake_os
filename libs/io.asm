disk_load:
	; loads dh sectors to es:bx from drive dl
	pusha
	
	push dx
	mov ah, 0x2
	mov al, dh
	mov ch, 0x0
	mov dh, 0x0
	mov cl, 0x2
	int 0x13

	jc disk_err1 

	pop dx
	cmp dh, al

	jne disk_err2
	jmp disk_load_exit
	
	disk_err1:
	pop dx
	disk_err2:
	mov bx, disk_err_mess
	call print_str

	disk_load_exit:
	popa
	ret

disk_err_mess:
	db "error while reading disk", 0x0