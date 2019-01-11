#!/bin/sh
set -e
. ./iso.sh

#-s -S
qemu-system-i386 -cdrom kernel.iso -d guest_errors -s -S
