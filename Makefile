OBJ_FILES = build/kernel_entry.o build/kernel.o build/low_level.o $(wildcard build/drivers/*.o) build/util.o

.PHONY: all start clean os-image

all: os-image

util.o:
	gcc -o build/util.o -c kernel/util.c -ffreestanding -m32 -fno-pie

drivers.o:
	cd build/drivers; gcc -c ../../kernel/drivers/*.c -ffreestanding -m32 -fno-pie

low_level.o: kernel/low_level.c
	gcc -o build/low_level.o -c kernel/low_level.c -ffreestanding -m32 -fno-pie

kernel.bin: kernel_entry.o kernel.o low_level.o drivers.o util.o
	ld -o build/kernel.bin -Ttext 0x1000 --oformat binary -m elf_i386 ${OBJ_FILES}

kernel.o: kernel/kernel.c
	gcc -fno-stack-protector -fno-pie -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o

kernel_entry.o: kernel/kernel_entry.asm
	nasm kernel/kernel_entry.asm -f elf -o build/kernel_entry.o

boot.bin: boot.asm
	nasm boot.asm -f bin -o build/boot.bin

os-image: kernel.bin boot.bin
	cat build/boot.bin build/kernel.bin > build/os-image

clean:
	rm build/*.o build/*.bin build/drivers/*.o

start: all
	qemu-system-x86_64 -s -drive file=build/os-image,format=raw,index=1,media=disk &
	# gdb -ex 'target remote localhost:1234'
		