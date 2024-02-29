GDT_start:
GDT_null:
	dd 0x0 
	dd 0x0 

GDT_code:
	dw 0xffff 
	dw 0x0 
	db 0x0 
	db 10011010b
	db 11001111b
	db 0x0 

GDT_data:
	dw 0xffff
	dw 0x0 
	db 0x0 
	db 10010010b
	db 11001111b
	db 0x0

GDT_end:

GDT_descriptor:
	dw GDT_end - GDT_start - 1
	dd GDT_start

CODE_SEGMENT equ GDT_code - GDT_start
DATA_SEGMENT equ GDT_data - GDT_start
