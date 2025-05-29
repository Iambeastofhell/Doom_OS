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

void strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] && i < 15) {  // Limit to 15 chars to leave room for null
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Ensure null termination
}