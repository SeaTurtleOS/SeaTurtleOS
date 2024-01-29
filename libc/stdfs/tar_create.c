#include <stdfs.h>
#include <algos.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

struct tart_fd tar_create(char* name, size_t size) {
    int fd;
    char** mapped;
    asm volatile (
        "movl $2, %%eax\n" // Syscall for open is 2
        "movl %0, %%edi\n" // Store filename in rdi
        "movl $65, %%esi\n" // Flag for open, read, write
        "movl $0644, %%edx\n"
        /*
            0644 = 
              0400 : Owner - read
            + 0200 : Owner - write
            + 0040 : Group - read
            + 0004 : Other - read
        */
       "syscall\n"
       : "=r" (fd)
       : "r" (name)
       : "eax", "edi", "esi", "edx"
    );

    if (fd < 0) {
        abort(); // Error!
    }

    asm volatile (
        "movl $9, %%eax\n" // Syscall for mmap
        "movl $0, %%edi\n" // Allow system to choose address
        "movl %0, %%esi\n" // Length of mapping in rsi
        "movl $3, %%edx\n" // Protection mode is PROT_READ | PROT_WRITE
        "syscall\n"
        "movl %%eax, %2\n" // Move result into mapped
        : "=r" (*mapped)
        : "r" (fd), "r" (size)
        : "eax", "edi", "esi", "edx"
    );

    if (*mapped == (char*)-1) {
        abort(); // Error!
    }

    struct tart tar_file = {
        .begin = **mapped,
        .name = {0},
        .mode = 006777,
        .owner_id = 0xffffffff,
        .group_id = 0xffffffff,
        .size = size,
        .last_modify = -1,
        .checksum = adler32(name),
        .file_type = REGTYPE,
        .linked_file = "",
        .ustar = "UStar",
        .ustar_v = "00",
        .owner_name = "",
        .group_name = "",
        .device_major = "",
        .device_minor = "",
        .prefix = "",
        .block = "",
        .next = NULL
    };

    struct tart* tar_p = &tar_file;
    struct tart_fd tfd = { &tar_p, fd };
    return tfd;
}