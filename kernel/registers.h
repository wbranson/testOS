#ifndef __REGISTERS_H
#define __REGISTERS_H

#include <stdint.h>

typedef struct registers
{
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_no;
    uint32_t err_no;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t usr_esp;
    uint32_t ss;
} registers_t;

#endif