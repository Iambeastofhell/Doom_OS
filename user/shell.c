#include "shell.h"
#include "string.h"
#include "standio.h"
#include "usersys.h"
#include "syscall.h"

void process_command(const char *str){
    if(strcmp(str, "clear")==0){
        vgainit();
    }else if(strncmp(str, "echo ", 5)==0){
        printf(str+5);
        printf("\n");
    }else if (strcmp(str, "testsys")==0){
        syscall(SYS_test, 0);
    }else if(strcmp(str, "help")==0){
        printf("Available commands :\n-> echo <string> : Prints the string to the screen\n-> clear : Clears the whole screen\n-> help : displays this help menu\n");
    }else{
        printf("Illegal command\n");
        printf("Available commands :\n-> echo <string> : Prints the string to the screen\n-> clear : Clears the whole screen\n-> help : displays this help menu\n");
    }
    printf("Vsh |> ");
}