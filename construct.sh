#!/bin/bash

BLUE="\033[0;36m"
GREEN="\033[0;32m"
RESET="\033[0m"

echo -e -n "${BLUE}Compiling bootloader .......... "
nasm -felf32 boot.s -o boot.o
echo -e "${GREEN}Success${RESET}"

echo -e -n "${BLUE}Building kernel ............... "
/home/tathya/opt/cross/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -O2 -Wall -Wextra -ffreestanding
echo -e "${GREEN}Success${RESET}"

echo -e -n "${BLUE}Linking kernel & bootloader ... "
/home/tathya/opt/cross/bin/i686-elf-gcc -T linker.ld -o seaturtleos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
echo -e "${GREEN}Success${RESET}"

echo -e -n "${BLUE}Copying binary into isodir .... "
cp seaturtleos.bin isodir/boot/seaturtleos.bin
echo -e "${GREEN}SUCCESS${RESET}"

echo -e -n "${BLUE}Creating iso images ........... "
grub-mkrescue -o seaturtleos.iso isodir >/dev/null
echo -e "${GREEN}Success${RESET}"

qemu-system-i386 -cdrom seaturtleos.iso