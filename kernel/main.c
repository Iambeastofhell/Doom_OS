#include "standio.h"
#include "keyboard.h"

void kmain(void) {
    vgainit();
    idt_init();
    kb_init();
    vga_printf("Kernel has started.\nWelcome to DOOM OS\n");
    while (1);    
    return;
}

