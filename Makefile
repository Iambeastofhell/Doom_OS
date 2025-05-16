CC=gcc
LD=ld
AS=nasm

CFLAGS=-m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib
LDFLAGS=-m elf_i386 -T linker.ld

OBJS=boot/bootloader.o kernel/main.o

all: kernel.bin

boot/bootloader.o: boot/bootloader.asm
	$(AS) -f elf32 $< -o $@

kernel/main.o: kernel/main.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -f $(OBJS) kernel.bin

