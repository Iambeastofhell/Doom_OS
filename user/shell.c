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
    }else if(strcmp(str, "ls")==0){
        syscall(SYS_fslist, 0, 0, 0, 0, 0);
    }else if(strncmp(str, "write ", 6)==0){
        char *filename, *data;
        parse_write_command(str, &filename, &data);
        syscall(SYS_write, 3, data, filename, 0, 0);
    }else if(strncmp(str, "read ", 5)==0){
        syscall(SYS_read, 3, str+5, 0, 0, 0);
    }else{
        printf(0, "Illegal command\n");
        printf(0, "Available commands :\n-> echo <string> : Prints the string to the screen\n-> clear : Clears the whole screen\n-> help : displays this help menu\n");
    }
    printf(0, "Vsh |> ");
}

void parse_write_command(char *input, char **filename, char **data) {
    // Skip "write " (6 characters)
    input += 6;

    // First token: filename
    *filename = input;

    // Find space after filename
    while (*input && *input != ' ') input++;

    if (*input == ' ') {
        *input = '\0';        // Null-terminate filename
        input++;              // Move to data
        *data = input;
    } 
}