typedef int (*fpn)(int, int, int);
#include "standio.h"
#include "registers.h"
#include "syscall.h"
#include "filesystem.h"

int sys_test(int a, int b, int c){
    vga_printf("syscall working\n");
    print_int(SYS_test);
    return 0;
}
int sys_write(int fd, char *buf, char *filename){
    if(fd==0 || fd ==1 || fd==2){
        vga_printf(buf);
    }else{
        fs_write(filename, buf, 50);
    }
}

int sys_read(int fd, char *filename){
    if (fd==0){
        vga_printf(filename);
    }else{
        char buf[256];
        fs_read(filename, buf);
        vga_printf(buf);
        vga_printf("\n");
    }
    
}

int sys_fslist(){
    char **ans = fs_list();
    for (int i = 0; ans[i]; i++){
        vga_printf(ans[i]);
        vga_printf("\n");
    }
    return 0;
}

fpn syscall_lst[]={
    [SYS_test] = sys_test,
    [SYS_write] = sys_write,
    [SYS_read] = sys_read,
    [SYS_fslist] = sys_fslist
};

void syscall_handler(struct registers_t *r){
    unsigned int sys_num = r->eax;
    int arg1 = r->ebx;
    int arg2 = r->ecx;
    int arg3 = r->edx;
    int arg4 = r->esi;
    int arg5 = r->edi;
    int arg6 = r->ebp;
    if(sys_num < sizeof(syscall_lst) / sizeof(fpn)){
        r->eax = syscall_lst[sys_num](arg1, arg2,arg3);
    }else{
        r->eax=-1;
    }
}