#include "usersys.h"
#include "syscall.h"
#include "standio.h"

void printf(int fd, char *buf){
    syscall(SYS_write, 1, (int)(buf), 0, 0, 0);
}