typedef int (*fpn)(int);
#include "standio.h"
#include "registers.h"
#include "syscall.h"

int sys_test(int a){
    printf("syscall working\n");
    print_int(SYS_test);
    return 0;
}

fpn syscall_lst[]={
    [SYS_test] = sys_test
};

void syscall_handler(struct registers_t *r){
    unsigned int sys_num = r->eax;
    int arg1 = r->ebx;
    if(sys_num < sizeof(syscall_lst) / sizeof(fpn)){
        r->eax = syscall_lst[sys_num](arg1);
    }else{
        r->eax=-1;
    }
}