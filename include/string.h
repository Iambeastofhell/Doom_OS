#ifndef STRING_H
#define STRING_H

int strlen(const char *str);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, int n);
void strcpy(char *dest, const char *src);

#endif