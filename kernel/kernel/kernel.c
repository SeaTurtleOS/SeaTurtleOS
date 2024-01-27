#include <stdio.h>
#include <kernel/tty.h>
#include <algos.h>
#include <stdint.h>
 
void kernel_main(void) {
	terminal_init();
	uint8_t* n = &"Hello World";
	uint8_t answer = crc32_byte(n, 32);
	printf("%d", answer);
}