#include <stdint.h>
#include <stddef.h>

#include "mystring.h"


uint32_t mystrlen(char *str)
{
    uint32_t res = 0;

    while (*str != 0) {
        res++;
        str += 1;
    }

    return res;
}


int myatoi(char c)
{
    return c - '0';
}
