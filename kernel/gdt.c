#include "gdt.h"
#include "alloc.h"

#define PAGE_SIZE 0x1000

static gdt_entry_t gdt_entries[6];
static gdt_register_t gdt_reg;

extern void gdt_flush(uint32_t);

static void
gdt_set_gate(uint32_t i, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access)
{
    gdt_entries[i].base_low = (base & 0xFFFF);
    gdt_entries[i].base_middle = (base >> 16) & 0xFF;
    gdt_entries[i].base_high = (base >> 24) & 0xFF;
    gdt_entries[i].limit_low = (limit & 0xFFFF);
    gdt_entries[i].flags = flags | ((limit >> 16) & 0x0F);
    gdt_entries[i].access = access;
}

void gdt_init(void)
{

    uint32_t gdt_addr = (uint32_t)&gdt_entries;
    gdt_tss_t tss;

    gdt_reg.limit = sizeof(gdt_entry_t) * 6 - 1;
    gdt_reg.base_low = gdt_addr & 0xFFFF;
    gdt_reg.base_high = (gdt_addr >> 16) & 0xFFFF;

    kmemset(gdt_entries, 0, sizeof(gdt_entry_t) * 6);

    gdt_set_gate(1, 0, 0xFFFFFFFF, 0xC0, 0x9A); // Kernel Code Segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0xC0, 0x92); // Kernel Data Segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xC0, 0xFA); // User Code Segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xC0, 0xF2); // User Data Segment

    gdt_set_gate(5, (uint32_t)&tss, sizeof(tss), 0x40, 0xE9);

    gdt_flush((uint32_t)&gdt_reg);
}