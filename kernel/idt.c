#include "idt.h"
#include "alloc.h"

extern void idt_flush(uint32_t);
extern void irq_remap();

static idt_entry_t idt_entries[256];
static idt_ptr_t idt_ptr;

extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);
extern void isr_21(void);
extern void isr_22(void);
extern void isr_23(void);
extern void isr_24(void);
extern void isr_25(void);
extern void isr_26(void);
extern void isr_27(void);
extern void isr_28(void);
extern void isr_29(void);
extern void isr_30(void);
extern void isr_31(void);

extern void irq_0(void);
extern void irq_1(void);
extern void irq_2(void);
extern void irq_3(void);
extern void irq_4(void);
extern void irq_5(void);
extern void irq_6(void);
extern void irq_7(void);
extern void irq_8(void);
extern void irq_9(void);
extern void irq_10(void);
extern void irq_11(void);
extern void irq_12(void);
extern void irq_13(void);
extern void irq_14(void);
extern void irq_15(void);

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags | 0x60;
}

void idt_init()
{

    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    kmemset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    irq_remap();

    idt_set_gate(0, (uint32_t)isr_0, 0x08, 0x8e);
    idt_set_gate(1, (uint32_t)isr_1, 0x08, 0x8e);
    idt_set_gate(2, (uint32_t)isr_2, 0x08, 0x8e);
    idt_set_gate(3, (uint32_t)isr_3, 0x08, 0x8e);
    idt_set_gate(4, (uint32_t)isr_4, 0x08, 0x8e);
    idt_set_gate(5, (uint32_t)isr_5, 0x08, 0x8e);
    idt_set_gate(6, (uint32_t)isr_6, 0x08, 0x8e);
    idt_set_gate(7, (uint32_t)isr_7, 0x08, 0x8e);
    idt_set_gate(8, (uint32_t)isr_8, 0x08, 0x8e);
    idt_set_gate(9, (uint32_t)isr_9, 0x08, 0x8e);
    idt_set_gate(10, (uint32_t)isr_10, 0x08, 0x8e);
    idt_set_gate(11, (uint32_t)isr_11, 0x08, 0x8e);
    idt_set_gate(12, (uint32_t)isr_12, 0x08, 0x8e);
    idt_set_gate(13, (uint32_t)isr_13, 0x08, 0x8e);
    idt_set_gate(14, (uint32_t)isr_14, 0x08, 0x8e);
    idt_set_gate(15, (uint32_t)isr_15, 0x08, 0x8e);
    idt_set_gate(16, (uint32_t)isr_16, 0x08, 0x8e);
    idt_set_gate(17, (uint32_t)isr_17, 0x08, 0x8e);
    idt_set_gate(18, (uint32_t)isr_18, 0x08, 0x8e);
    idt_set_gate(19, (uint32_t)isr_19, 0x08, 0x8e);
    idt_set_gate(20, (uint32_t)isr_20, 0x08, 0x8e);
    idt_set_gate(21, (uint32_t)isr_21, 0x08, 0x8e);
    idt_set_gate(22, (uint32_t)isr_22, 0x08, 0x8e);
    idt_set_gate(23, (uint32_t)isr_23, 0x08, 0x8e);
    idt_set_gate(24, (uint32_t)isr_24, 0x08, 0x8e);
    idt_set_gate(25, (uint32_t)isr_25, 0x08, 0x8e);
    idt_set_gate(26, (uint32_t)isr_26, 0x08, 0x8e);
    idt_set_gate(27, (uint32_t)isr_27, 0x08, 0x8e);
    idt_set_gate(28, (uint32_t)isr_28, 0x08, 0x8e);
    idt_set_gate(29, (uint32_t)isr_29, 0x08, 0x8e);
    idt_set_gate(30, (uint32_t)isr_30, 0x08, 0x8e);
    idt_set_gate(31, (uint32_t)isr_31, 0x08, 0x8e);

    idt_set_gate(32, (uint32_t)irq_0, 0x08, 0x8e);
    idt_set_gate(33, (uint32_t)irq_1, 0x08, 0x8e);
    idt_set_gate(34, (uint32_t)irq_2, 0x08, 0x8e);
    idt_set_gate(35, (uint32_t)irq_3, 0x08, 0x8e);
    idt_set_gate(36, (uint32_t)irq_4, 0x08, 0x8e);
    idt_set_gate(37, (uint32_t)irq_5, 0x08, 0x8e);
    idt_set_gate(38, (uint32_t)irq_6, 0x08, 0x8e);
    idt_set_gate(39, (uint32_t)irq_7, 0x08, 0x8e);
    idt_set_gate(40, (uint32_t)irq_8, 0x08, 0x8e);
    idt_set_gate(41, (uint32_t)irq_9, 0x08, 0x8e);
    idt_set_gate(42, (uint32_t)irq_10, 0x08, 0x8e);
    idt_set_gate(43, (uint32_t)irq_11, 0x08, 0x8e);
    idt_set_gate(44, (uint32_t)irq_12, 0x08, 0x8e);
    idt_set_gate(45, (uint32_t)irq_13, 0x08, 0x8e);
    idt_set_gate(46, (uint32_t)irq_14, 0x08, 0x8e);
    idt_set_gate(47, (uint32_t)irq_15, 0x08, 0x8e);

    idt_flush((uint32_t)&idt_ptr);
}
