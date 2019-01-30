
#include <stdbool.h>
#include "irq.h"
#include "io.h"

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)

#define IRQ_HDNLR_SIZE 16

static irq_handler_t irq_handlers[IRQ_HDNLR_SIZE];
static bool _irq_init = false;

static void _init()
{
    if (_irq_init)
        return;

    for (int i = 0; i < IRQ_HDNLR_SIZE; i++)
    {
        irq_handlers[i] = 0;
    }
    _irq_init = true;
}

void irq_remap(void)
{
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1, 0x11);
    io_wait();
    outb(PIC2, 0x11);
    io_wait();
    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();
    outb(PIC1_DATA, 0x04);
    io_wait();
    outb(PIC2_DATA, 0x02);
    io_wait();
    outb(PIC1_DATA, 0x01);
    io_wait();
    outb(PIC2_DATA, 0x01);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
    io_wait();

    // outb(PIC1_DATA, 0x0);
    // io_wait();
    // outb(PIC2_DATA, 0x0);
    // io_wait();
}

void irq_register_handler(uint8_t num, irq_handler_t handler)
{
    if (!_irq_init)
        _init();

    irq_handlers[num] = handler;
}

void irq_handler(registers_t reg)
{
    uint8_t irq_n = reg.int_no % 32;

    if (irq_handlers[irq_n] != 0)
    {
        irq_handler_t hndlr = irq_handlers[irq_n];
        hndlr(reg);
    }

    if (reg.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    outb(0x20, 0x20);
}