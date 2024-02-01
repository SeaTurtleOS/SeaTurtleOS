#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>
 
void kernel_main(void) {
	terminal_init();
	unsigned char fetch = fetch_kb();
	printf("%c, %d, %d\n", fetch, fetch, (int) fetch);
//	putchar((int) fetch);
}