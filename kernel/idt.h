#ifndef __IDT_H
#define __IDT_H

#include <stdint.h>

typedef struct idt_entry
{
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

/**
 * Initialize the Global Descriptor Table.
 */
void idt_init(void);

#endif