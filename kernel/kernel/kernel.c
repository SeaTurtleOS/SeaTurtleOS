#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>
 
void kernel_main(void) {
	terminal_init();
	printf("Hello, World!");
}