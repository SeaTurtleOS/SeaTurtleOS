#include <stdio.h>

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
//    printf("hi! ;%c;", rv);
    return rv;
}