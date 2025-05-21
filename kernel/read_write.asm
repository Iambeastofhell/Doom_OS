global read_port
read_port:
    mov edx, [esp + 4]   
    in al, dx            
    ret          
        
global write_port
write_port:
    mov edx, [esp + 4]      
    mov al, [esp + 8]     
    out dx, al            
    ret

extern keyboard_handler_main
global keyboard_handler
keyboard_handler:                 
	call    keyboard_handler_main
	iretd

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret