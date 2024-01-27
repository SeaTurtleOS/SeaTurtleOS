#include <stdio.h>
#include <kernel/tty.h>
#include <algos.h>
#include <stdint.h>
 
void kernel_main(void) {
	terminal_init();
	char name[] = "Turtle";
	printf("God's most beloved angel is named... %s", name);
}