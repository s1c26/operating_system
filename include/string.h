#ifndef _STRING_H
#define _STRING_H

#include <stdlib.h>

char *itoa(int value, char *buffer, int base);

size_t strlen(const char *str);

char *strrev(char *str);

#endif
