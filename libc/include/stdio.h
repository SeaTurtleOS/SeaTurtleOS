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

#ifdef __cplusplus
}
#endif
 
#endif