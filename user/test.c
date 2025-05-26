#include "usersys.h"
#include "syscall.h"

void main(){
    syscall(SYS_test, 0, 0, 0 ,0 ,0);
}