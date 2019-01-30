#include "isr.h"
#include <stdbool.h>

#define ISR_HNDLR_SIZE 256
isr_handler_t isr_handlers[ISR_HNDLR_SIZE];

static bool _isr_init = false;

static void _init()
{
    if (_isr_init)
        return;

    for (int i = 0; i < ISR_HNDLR_SIZE; i++)
    {
        isr_handlers[i] = 0;
    }
}

void isr_register_handler(uint8_t num, isr_handler_t func)
{
    if (!_isr_init)
        _init();

    isr_handlers[num] = func;
}

void isr_handler(registers_t reg)
{
    if (reg.int_no > 0 && reg.int_no < 256 && isr_handlers[reg.int_no] != 0)
    {
        isr_handlers[reg.int_no](reg);
    }
}