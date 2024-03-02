[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
call switch2pm
jmp $

%include "libs/io.asm"
%include "libs/gdt.asm"
%include "libs/print.asm"
%include "libs/print_pm.asm"
%include "libs/switch2pm.asm"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET
	mov dh, 25
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_PM:
	call clear_screen_pm
	call KERNEL_OFFSET

	jmp $

BOOT_DRIVE: db 0x0
MESS_REAL_MODE: db "Started in real mode", 0x0
MESS_LOAD_KERNEL: db "Loading kernel", 0x0
MESS_STARTED_PROT_MODE: db "Protected mode started", 0x0

times 510 - ($ - $$) db 0x0
dw 0xaa55
