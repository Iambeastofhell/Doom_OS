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

void printf(const char* str){
    while (*str){
        if(*str=='\n'){
            cursor_x=0;
            cursor_y++;
        }else{
            int index = (cursor_y*80 +cursor_x)*2;
            vidptr[index] = *str;
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
        str++;
    }
}