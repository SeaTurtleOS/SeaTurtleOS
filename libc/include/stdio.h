#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif
 
void printf(const char*, ...);
void putchar(int);
void puts(const char*);
unsigned char inportb(unsigned short);
void outportb (unsigned short _port, unsigned char _data);
unsigned char fetch_kb(void);

#ifdef __cplusplus
}
#endif
 
#endif