#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_WHITE = 7,
    VGA_GRAY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_YELLOW = 14,
    VGA_BRIGHT_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    // Color is fetched from vga_entry_color function;
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;  // X-axis terminal size limit
static const size_t VGA_HEIGHT = 25; // Y-axis terminal size limit

size_t terminal_row; // X offset
size_t terminal_column; // Y offset
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void) {
    terminal_row = 0;
    terminal_column = 0;
    // Initialize the current row and column to be at the beginning of the terminal
    terminal_color = vga_entry_color(VGA_LIGHT_RED, VGA_BLACK);  // Blue foreground, black background
    terminal_buffer = (uint16_t*) 0xB8000;  // Spooky magic number!?
    for (size_t y=0;y<VGA_HEIGHT;y++) {  // Goes over every line (row)
        for (size_t x=0;x<VGA_WIDTH;x++) { // Goes over every column
            const size_t index = y * VGA_WIDTH + x;  // Position = y*width+x, covers 'y' number of lines and adds offset of x
            terminal_buffer[index] = vga_entry(' ', terminal_color);  // Initialize with blank characters (spaces) in every position
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;  // I mean, duh
}

void terminal_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
    /*
    c - Character you want to put
    color - Color of the character
    x, y - inteneded x and y offsets of the character
    */
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_put_char(char c) {
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
        return;
    }
    terminal_put_entry_at(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) { // Goes to next column, even if condition is not met
        terminal_column = 0; // Wraps to beginning of line
        if (++terminal_row == VGA_HEIGHT) { // Goes to next line, even if condition is not met
            terminal_row = 0; // Wraps to beginning of terminal
        }
    }
}

void terminal_write(const char* data, size_t size) {
    // The size parameter just holds the length of data
    for (size_t i = 0; i < size; i++) {
        terminal_put_char(data[i]); // Display the ith character
    }
}

void terminal_write_string(const char* data) {
    // Use the strlen function we umpletemented above to get data's length
    terminal_write(data, strlen(data));
}

void kernel_main(void) {
    terminal_init();
    terminal_write_string("Hello, Sea turtles!\n");
    terminal_write_string("Hello to you too, tortoises!");
}
