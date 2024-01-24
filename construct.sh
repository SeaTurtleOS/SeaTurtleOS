#!/bin/bash

BLUE="\033[0;36m"
RESET="\033[0m"
/home/tathya/opt/cross/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -O2 -Wall -Wextra -ffreestanding
echo -e "${BLUE}Successfully compiled kernel${RESET}"
/home/tathya/opt/cross/bin/i686-elf-gcc -T linker.ld -o seaturtleos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
echo -e "${BLUE}Successfully linked bootloader and kernel${RESET}"
cp seaturtleos.bin isodir/boot/seaturtleos.bin
echo -e "${BLUE}Copied binary into boot folder${RESET}"
grub-mkrescue -o seaturtleos.iso isodir
echo -e "${BLUE}Successfully made iso image${RESET}"
qemu-system-i386 -cdrom seaturtleos.iso