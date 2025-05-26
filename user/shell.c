#include "shell.h"
#include "string.h"
#include "standio.h"
#include "usersys.h"
#include "syscall.h"

void process_command(const char *str){
    if(strcmp(str, "clear")==0){
        vgainit();
    }else if(strncmp(str, "echo ", 5)==0){
        printf(0, str+5);
        printf(0, "\n");
    }else if (strcmp(str, "testsys")==0){
        syscall(SYS_test, 0, 0, 0, 0, 0);
    }else if(strcmp(str, "help")==0){
        printf(0, "Available commands :\n-> echo <string> : Prints the string to the screen\n-> clear : Clears the whole screen\n-> help : displays this help menu\n");
    }else{
        printf(0, "Illegal command\n");
        printf(0, "Available commands :\n-> echo <string> : Prints the string to the screen\n-> clear : Clears the whole screen\n-> help : displays this help menu\n");
    }
    printf(0, "Vsh |> ");
}