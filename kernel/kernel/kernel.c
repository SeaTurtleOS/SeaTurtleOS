#include <stdio.h>
#include <kernel/tty.h>
 
void kernel_main(void) {
	terminal_init();
	printf("Hello, World!\n");
}