Build test:

![C/C++ Workflow Status](https://github.com/Iambeastofhell/Doom_OS/actions/workflows/c-cpp.yml/badge.svg)


The goal of DoomOS is to build a simple, custom operating system for x86 (32-bit) architecture, with the eventual capability to run the classic DOOM game.

Requirements:
Make sure you have the following tools installed:
- nasm – for assembling bootloader and low-level code
- gcc – with multilib support (for 32-bit compilation)
- ld – the GNU linker
- qemu-system-i386 – to emulate the OS

Install them using:
```bash
sudo apt install nasm gcc qemu-system build-essential
```

To run:
```bash
make run
``` 
If you want to clean and rebuild again
```bash
make clean 
make
make run
```