#include "boot/multiboot.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "lib/stdio.h"

void kernel_main(multiboot_info_t *mbd, unsigned int magic)
{
    magic = magic;
    mbd = mbd;

    term_init();

    kprintf("Loading GDT\n");
    gdt_init();

    kprintf("Loading IDT\n");
    idt_init();

    while (1)
        ;
}
