#include <stdfs.h>

struct tart** tar_create(char* name) {
    int descriptor;

    asm volatile (
        "mov $8, %%eax\n"
        "mov %1, %%ebx\n"
        "mov $0666 %%ecx\n"
        "int $0x80\n"
        : "=r" (descriptor)
        : "r"  (name)
        : "%eax", "%ebx", "%ecx"
    );

    if (descriptor >= 0) {
        asm volatile (
            "mov %0, %%edi\n"
            "mov $6, %%eax\n"
            "int $0x80\n"
            :
            : "r" (descriptor)
            : "%eax", "%edi"
        );
    }

    // TODO: Complete writing the initalization of the tar object
    // struct tart tar = {
    //     name
    // }
    return 0;
}