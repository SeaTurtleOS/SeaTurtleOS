#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;  // X-axis terminal size limit
static const size_t VGA_HEIGHT = 25; // Y-axis terminal size limit

static size_t terminal_row; // X offset
static size_t terminal_column; // Y offset
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_init(void) {
    terminal_row = 0;
    terminal_column = 0;
    // Initialize the current row and column to be at the beginning of the terminal
    terminal_color = vga_entry_color(VGA_LIGHT_CYAN, VGA_BLACK);  // Blue foreground, black background
    terminal_buffer = (uint16_t*) 0xB8000;  // Spooky magic number!?
    for (size_t y = 0; y < VGA_HEIGHT; y++) {  // Goes over every line (row)
        for (size_t x = 0;x < VGA_WIDTH; x++) { // Goes over every column
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

void terminal_shift_character(size_t i, size_t j) {
    terminal_buffer[(i-1) * VGA_WIDTH + j] = terminal_buffer[i * VGA_WIDTH + j]; // Moving over the information, one character at a time.
}

void terminal_shift_text(void) {
    // Moves the contents of the terminal_buffer 1 line upwards
    for (size_t i = 1; i <= VGA_HEIGHT; i++) { // Starting i at 1 so the topmost line gets deleted
        for (size_t j = 0; j < VGA_WIDTH; j++) {
            terminal_shift_character(i, j); // Shift every character upwards.
        }
    }
    if (terminal_row != VGA_HEIGHT-1) { // VGA_HEIGHT-1 is the final line
        terminal_row--; // Go to the previous line if we're not at the end of the buffer.
    }
}

void terminal_put_char(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (terminal_row == VGA_HEIGHT-1) {
            terminal_shift_text();  // Don't go to the next terminal row, because there is none. VGA_HEIGHT-1 is the last row.
        } else {
            terminal_row++;
        }
    } else {
        if (terminal_column == VGA_WIDTH-1) {
            terminal_column = 0; 
            // Overflow onto the next column  vvvv
            if (terminal_row == VGA_HEIGHT-1) {
                terminal_shift_text(); // Shift text in order to start the overflow
            } else {
                terminal_row++; // Just go to the next line
            }
        }
        terminal_put_entry_at(c, terminal_color, terminal_column, terminal_row);
        terminal_column++; // Next character position
    }
}

void terminal_write(const char* data, size_t size) {
    // The size parameter just holds the length of data
    for (size_t i = 0; i < size; i++) {
        if (data[i] == '\0') {return;}
        terminal_put_char(data[i]); // Display the ith character
    }
}

void terminal_write_string(const char* data) {
    // Use the strlen function we umpletemented above to get data's length
    terminal_write(data, strlen(data));
}

void terminal_print(const char* data) {
    terminal_write_string(data);  // Print the text, then the newline
    terminal_write_string("\n");
}