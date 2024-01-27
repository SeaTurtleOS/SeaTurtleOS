#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <algos.h>
 
static void print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		putchar(bytes[i]);
}
 
void printf(const char* text, ...) {
    va_list ptr;
    va_start(ptr, text);
    int length = strlen(text);
    bool format = false;
    for (int i = 0; i < length; i++) {
        // Not in format mode, not going to enter format mode:
        if (!format && text[i] != '%') {
            print(&text[i], 1);
        }

        // In format mode already
        if (format) {
            // Format in a digit
            if (text[i] == 'd') {
                char v[32]; // 32 is an arbitrary number (i think?)
                int_to_string(v, va_arg(ptr, int));
                for (int i = 0; v[i] != '\0'; i++)
                    print(&v[i], 1); // Display a single character. There's probably a better way to do this, but I'm too lazy to figure that out.
            } else if (text[i] == 'c') {
                // Print the one character
                print((char*) va_arg(ptr, int), 1);
            } else if (text[i] == 's') {
                char* items = va_arg(ptr, char*);
                // Iterate over the characters in a string one by one
                for (int i = 0; items[i] != '\0'; i++)
                    print(&items[i], 1);
            }
            // Exit format mode
            format = false;
        }

        // About to enter format mode
        if (text[i] == '%') {
            format = true;
        }
    }
	va_end(ptr);
}