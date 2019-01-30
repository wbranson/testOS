#ifndef __ISR_H
#define __ISR_H

#include <stdint.h>
#include "registers.h"

void isr_handler(registers_t reg);
typedef void (*isr_handler_t)(registers_t reg);

void isr_register_handler(uint8_t num, isr_handler_t func);

#endif