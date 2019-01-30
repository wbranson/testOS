#ifndef __IRQ_H
#define __IRQ_H

#include <stdint.h>
#include "registers.h"

void irq_handler(registers_t reg);
typedef void (*irq_handler_t)(registers_t reg);

void irq_register_handler(uint8_t num, irq_handler_t func);

#endif