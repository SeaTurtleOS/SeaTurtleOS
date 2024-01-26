#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/seaturtleos.kernel isodir/boot/seaturtleos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "seaturtleos" {
	multiboot /boot/seaturtleos.kernel
}
EOF
grub-mkrescue -o seaturtleos.iso isodir