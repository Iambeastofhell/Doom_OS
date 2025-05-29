#include "standio.h"
#include "keyboard.h"
#include "filesystem.h"

void kmain(void) {
    vgainit();
    idt_init();
    kb_init();
    vga_printf("Kernel has started.\nWelcome to DOOM OS\nVsh |> ");
    fs_init();
    fs_write("TEST1.txt", "THis is a test from the first file, ",36);
    fs_write("TEST2.txt", "Testing from the 2nd file is htis??, ",36);
    char a[50];
    char b[50];
    fs_read("TEST2.txt", a);
    fs_read("TEST1.txt", b);
    vga_printf("this is a :");
    vga_printf(a);
    vga_printf("\n");
    vga_printf(b);
    vga_printf("\n");
    while (1);    
    return;
}

