void tar_close(int fd) {
    asm volatile (
        "mov $3, %%eax\n" // Close
        "mov %0, %%edi\n" // File descriptor
        "syscall"
        :
        : "r" (fd)
        : "eax", "edi"
    );
}