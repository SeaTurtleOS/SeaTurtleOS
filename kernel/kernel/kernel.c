#include <stdio.h>
#include <kernel/tty.h>
#include <stdfs.h>
#include <stdint.h>
 
void kernel_main(void) {
	terminal_init();
	char* name = "turts.txt";
	size_t size = 4096;
	struct tart_fd fd = tar_create(name, size);
	tar_close(fd.fd);
}