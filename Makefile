_ := $(shell test -d build/drivers || mkdir -p build/drivers)
# remember to write everything u add to the end of the OBJ_FILES variable!!!
OBJ_FILES =  build/kernel_entry.o build/kernel.o build/low_level.o $(wildcard build/drivers/*.o) build/util.o build/idt.o build/idts.o build/timer.o
GCC_FLAGS = -c -ffreestanding -m32 -fno-pie -fno-stack-protector

.PHONY: all start clean os-image

all: os-image

timer.o:
	gcc $(GCC_FLAGS) -o build/timer.o kernel/timer.c

idt.o:
	gcc $(GCC_FLAGS) -o build/idt.o kernel/idt/idt.c

idts.o:
	nasm -f elf -o build/idts.o kernel/idt/idt.asm

util.o:
	gcc $(GCC_FLAGS) -o build/util.o kernel/util.c

drivers.o:
	cd build/drivers; gcc $(GCC_FLAGS) ../../kernel/drivers/*.c

low_level.o: kernel/low_level.c
	gcc $(GCC_FLAGS) -o build/low_level.o kernel/low_level.c

kernel.bin: kernel_entry.o kernel.o low_level.o drivers.o util.o idt.o idts.o timer.o 
	ld -o build/kernel.bin -Ttext 0x1000 --oformat binary -m elf_i386 ${OBJ_FILES}

kernel.o: kernel/kernel.c
	gcc $(GCC_FLAGS) kernel/kernel.c -o build/kernel.o

kernel_entry.o: kernel/kernel_entry.asm
	nasm kernel/kernel_entry.asm -f elf -o build/kernel_entry.o

boot.bin: boot.asm
	nasm boot.asm -f bin -o build/boot.bin

os-image: kernel.bin boot.bin
	cat build/boot.bin build/kernel.bin > build/os-image

clean:
	rm -rf build

start:
	qemu-system-x86_64 -s -drive file=build/os-image,format=raw,index=1,media=disk &
	# gdb -ex 'target remote localhost:1234'
		