global isr_syscall
extern syscall_handler
isr_syscall:
    pusha                   
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp               ;wasted hours here because had not pushed the registers before calling the c function
    call syscall_handler   
    add esp, 4 

    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret                    
