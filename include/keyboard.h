#ifndef KEYBOARD_H
#define KEYBOARD_H

void idt_init(void);
void kb_init(void);
void keyboard_handler_main(void);
void set_idt_entry(int n, unsigned int handler);

#endif
