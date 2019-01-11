PWD=$(shell pwd)
SYSROOT=${PWD}/sysroot
HOST=i686-elf
AR=${HOST}-ar
AS=${HOST}-as
CC=${HOST}-gcc --sysroot=${SYSROOT}

KERNEL_ARCH_OBJS=$(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_ARCH_OBJS+=$(patsubst %.S,%.o,$(wildcard kernel/*.S))

CFLAGS=-Og -g -ffreestanding -Wall -Wextra

CFLAGS:=$(CFLAGS) 
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS) 
LIBS:=$(LIBS) -nostdlib 

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) 

OBJS=\
$(KERNEL_OBJS) \


LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

.PHONY: all clean 
.SUFFIXES: .o .c .S

all: kernel.img

kernel.img: $(OBJS) kernel/linker.ld
	$(CC) -T kernel/linker.ld -o $@ $(CFLAGS)  $(LINK_LIST)
	grub-file --is-x86-multiboot kernel.img

kernel/crtbegin.o kernel/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f kernel.img
	rm -f kernel.iso
	rm -rf isodir
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

-include $(OBJS:.o=.d)