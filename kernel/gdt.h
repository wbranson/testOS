#ifndef __GDT_H
#define __GDT_H

#include <stdint.h>

typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_register
{
    uint16_t limit;
    uint16_t base_low;
    uint16_t base_high;
} __attribute__((packed)) gdt_register_t;

typedef struct gdt_tss
{
    uint32_t prev;
    uint32_t esp0; /* Stack pointer when we change to kernel mode */
    uint32_t ss0;  /* Stack segment when we change to kernel mode */
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;

} __attribute__((packed)) gdt_tss_t;

void gdt_init(void);

#endif