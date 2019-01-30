#ifndef __VIDMEM_H
#define __VIDMEM_H

#include <stdint.h>
#include <stddef.h>

typedef enum vm_color
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    Lt_Gray,
    Dk_Gray,
    Lt_Blue,
    Lt_Green,
    Lt_Cyan,
    Lt_Red,
    Lt_Magenta,
    Lt_Brown,
    White
} VM_Color;

void vm_putch(char c);
void vm_puts(const char *data, size_t size);
void vm_fg(VM_Color color);
void vm_bg(VM_Color color);
void vm_newline();
void vm_cursor_pos(short x, short y);

#endif