#include <stdlib.h>

char *itoa(int value, char *buffer, int base)
{
    if(base > 36 || base < 2)
        return NULL;
    
    char *digits_start = buffer;
    if(base == 10 && value < 0)
    {
        value = -value;
        *digits_start++ = '-';
    }
    
    char *dest = buffer;

    do {
        *dest++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value / base];
        value = value / base;
    } while(value > 0);

    *dest = '\0';
    strrev(digits_start);

    return buffer;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    
    while(*str++ != '\0')
        len++;
        
    return len;
}

char *strrev(char *str)
{
    char *start = str;
    char *end = str + strlen(str) - 1;
    char temp;
    while(end > start)
    {
        temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    return str;
}
