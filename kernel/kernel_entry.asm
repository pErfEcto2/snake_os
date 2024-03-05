[bits 32]
[extern main]
[extern init_idt]
[extern init_timer]
[extern init_keyboard]
call init_idt
call init_timer
call init_keyboard
call main
cli
hlt
