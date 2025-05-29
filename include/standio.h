#ifndef STANDIO_H
#define STANDIO_H

void vga_printf(const char* str);
void printf(int fd, char *buf);
void vgainit();
void backspace();
char putchar(const char c);
void print_int(int n);
void *memcpy(void *dest, void *src, int n);

#endif