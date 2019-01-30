#include "io.h"

void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1\n\t"
                 : /* no outputs. */
                 : "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;

    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));

    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret;

    asm volatile("inw %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));

    return ret;
}

void pause(void)
{
    asm volatile("pause");
}

void io_wait(void)
{
    outb(0x80, 0);
}