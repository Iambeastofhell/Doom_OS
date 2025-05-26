typedef int (*fpn)(int, int);
#include "standio.h"
#include "registers.h"
#include "syscall.h"

int sys_test(int a){
    vga_printf("syscall working\n");
    print_int(SYS_test);
    return 0;
}
int sys_write(int fd, char *buf){
    if(fd==0 | fd ==1){
        vga_printf(buf);
    }
}


fpn syscall_lst[]={
    [SYS_test] = sys_test,
    [SYS_write] = sys_write
};

void syscall_handler(struct registers_t *r){
    unsigned int sys_num = r->eax;
    int arg1 = r->ebx;
    int arg2 = r->ecx;
    if(sys_num < sizeof(syscall_lst) / sizeof(fpn)){
        r->eax = syscall_lst[sys_num](arg1, arg2);
    }else{
        r->eax=-1;
    }
}