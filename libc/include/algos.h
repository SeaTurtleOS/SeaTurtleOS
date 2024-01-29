#ifndef _ALGOS_H
#define _ALGOS_H 1
 
#include <sys/cdefs.h>
#include <stdint.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
uint32_t crc32_byte(uint8_t *p, uint32_t bytelength);
void int_to_string(char str[], int num);
uint32_t adler32(char*);

#ifdef __cplusplus
}
#endif
 
#endif