#!/bin/sh
set -e

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp kernel.img isodir/boot/kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "kernel" {
	multiboot /boot/kernel
}
EOF
grub-mkrescue -o kernel.iso isodir
