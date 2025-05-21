int strlen(const char *str){
    int len=0;
    while(*str++){
        len++;
    }
    return len;
}

int strcmp(const char *str1, const char *str2){
    while(*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, int n){
    while(n--){
        if(*str1!=*str2 || *str1 =='\0' || *str2 == '\0'){
            return *(unsigned char *)str1 - *(unsigned char *)str2;
        }
        str1++;
        str2++;
    }
    return 0;
}