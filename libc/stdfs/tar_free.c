#include <stdfs.h>
#include <stdlib.h>

void tar_free(struct tart * archive) {
    while (archive) {
        struct tart* next = archive -> next;
        free(archive);
        archive = next;
    }
}
