[bits 32]
[extern main]
[extern initIdt]
[extern init_timer]
call initIdt
call init_timer
call main
cli
hlt
