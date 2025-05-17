CC = gcc
LD = ld
AS = nasm

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -Iinclude
LDFLAGS = -m elf_i386 -T linker.ld

C_SOURCES := $(wildcard kernel/*.c lib/*.c)
ASM_SOURCES := $(wildcard boot/*.asm)

C_OBJS := $(C_SOURCES:.c=.o)
ASM_OBJS := $(ASM_SOURCES:.asm=.o)

OBJS = $(ASM_OBJS) $(C_OBJS)

all: kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) -f elf32 $< -o $@

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -f $(OBJS) kernel.bin