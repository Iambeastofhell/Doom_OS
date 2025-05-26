#include "standio.h"

int cursor_x=0, cursor_y=0;
char* vidptr = (char *)0xb8000;

void vgainit(){
    unsigned int j=0;
    while (j<80*25*2){
        vidptr[j]=' ';
        vidptr[j+1]=0x07;
        j=j+2;
    }
    cursor_x=0;
    cursor_y=0;
}

void scrollup(){
    for(int i=0;i<80*24*2;i++){
        vidptr[i] = vidptr[160+i];
    }
    for(int i=0;i<160;i+=2){
        vidptr[80*2*24+i]=' ';
        vidptr[80*2*24+i+1]=0x07;
    }
    cursor_x=0;
    cursor_y--;
}

char putchar(const char c){
    if(c=='\n'){
        cursor_x=0;
        cursor_y++;
    }else{
        int index = (cursor_y*80 +cursor_x)*2;
        vidptr[index] = c;
        vidptr[index+1]=0x04;
        cursor_x++;
    }
    if(cursor_x>=80){
        cursor_x=0;
        cursor_y++;
    }
    if (cursor_y>=25){
        scrollup();
    }
    return c;
}

void backspace(){
    if(cursor_x==0){
        if(cursor_y!=0){
            cursor_y--;
            cursor_x=79;
            int index = (cursor_y*80 +cursor_x)*2;
            vidptr[index] = ' ';
            vidptr[index+1] = 0x04;
        }
    }else{
        cursor_x--;;
        int index = (cursor_y*80 +cursor_x)*2;
        vidptr[index] = ' ';
        vidptr[index+1] = 0x04;
    }
}

void vga_printf(const char* str){
    while (*str){
        putchar(*str);
        str++;
    }
}



// Convert an integer to a string (char*) without using standard libraries
char* int_to_str(int n) {
    static char str[12]; // Enough to hold -2147483648 + null terminator
    int i = 10;           // Start from end of buffer (excluding null terminator)
    int is_negative = 0;
    
    str[11] = '\0';       // Null-terminate the string

    if (n == 0) {
        str[i] = '0';
        return &str[i];
    }

    if (n < 0) {
        is_negative = 1;
    }

    // Handle each digit
    while (n != 0) {
        int digit = n % 10;
        if (digit < 0) digit = -digit;
        str[i--] = '0' + digit;
        n /= 10;
    }

    if (is_negative) {
        str[i--] = '-';
    }

    return &str[i + 1];
}


void print_int(int n) {
    vga_printf(int_to_str(n));
}
