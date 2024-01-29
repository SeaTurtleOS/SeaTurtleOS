#include <string.h>
#include <stdint.h>

// Fetches the adler32 checksum on a given target string
uint32_t adler32(char* text) {
    size_t len = strlen(text);
    int A = 1;
    int B = 0;
    for (size_t i = 0; i < len; i++) {
        A += (int) text[i];
        B += A;
    }
    A = A % 65521;
    B = B % 65521;
    return B * 65536 + A;
}