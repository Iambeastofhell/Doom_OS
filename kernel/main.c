#include "standio.h"
#include "keyboard.h"
#include "filesystem.h"

void kmain(void) {
    vgainit();
    idt_init();
    kb_init();
    fs_init();
    vga_printf("Kernel has started.\nWelcome to DOOM OS\nVsh |> ");
    while (1);    
    return;
}

