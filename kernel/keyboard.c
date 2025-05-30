#define IDT_SIZE 256
#include "standio.h"
#include "keyboard_map.h"
#include "shell.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0xee
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern void isr_syscall(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

char input_buffer[256];
int buffer_index=0;
// IDT entry structure
struct IDT_entry {
    unsigned short offset_lowerbits;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higherbits;
};

// Declare IDT
struct IDT_entry IDT[IDT_SIZE];

void set_idt_entry(int n, unsigned int handler){
	IDT[n].offset_lowerbits = handler & 0XFFFF;
	IDT[n].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[n].zero = 0;
	IDT[n].type_attr = INTERRUPT_GATE;
	IDT[n].offset_higherbits = (handler & 0xffff0000) >> 16;
}


void idt_init(void)
{
	set_idt_entry(0x80, (unsigned long)isr_syscall);   //software interrupts
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	set_idt_entry(0x21, (unsigned long)keyboard_handler); // keyboard interrupt

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

// This is called from the ASM stub keyboard_handler

void keyboard_handler_main(void)
{
	unsigned char status;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		if(keycode == ENTER_KEY_CODE) {
            vga_printf("\n");
            input_buffer[buffer_index]='\0';
            process_command(input_buffer);
            for (int i = 0; i < buffer_index; i++){
                input_buffer[buffer_index]=' ';
            }
            buffer_index=0;
			return;
		}
		if(keycode == 0x0E) {   //14 which would correspond to backspace
            backspace();
            input_buffer[--buffer_index]=' ';
			return;
		}
        input_buffer[buffer_index++] = putchar(keyboard_map[(unsigned char) keycode]);
	}
}