// kernel/main.c
void kmain(void) {
    const char* str = "WELCOME TO THE DOOM OS";
    char* vidptr = (char *)0xb8000;
    unsigned int j=0;
    while (j<80*25*2){
        vidptr[j]=' ';
        vidptr[j+1]=0x07;
        j=j+2;
    }
    j=0;
    unsigned int i=0;
    while (str[j]){
        vidptr[i] = str[j++];
        vidptr[i+1]=0x04;
        i+=2;
    }
    return;
}

