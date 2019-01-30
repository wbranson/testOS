#include "vidmem.h"

#define VIDEO_MEM_ADDR 0xB8000
#define VIDEO_MEM_COLS 80
#define VIDEO_MEM_ROWS 25

static int cursor_pos_x, cursor_pos_y;
static uint16_t *video_buffer = (uint16_t *)0XB8000;
static unsigned char _attributes;
static inline short vm_vga_entry(char uc)
{
    return (uint16_t)uc | _attributes << 8;
}

void vm_putch(char c)
{
    int idx = 0;
    if (++cursor_pos_x >= VIDEO_MEM_COLS)
    {
        cursor_pos_x = 0;
        cursor_pos_y++;
    }

    if (cursor_pos_y >= VIDEO_MEM_ROWS)
    {
        cursor_pos_y = 0;
    }

    idx = cursor_pos_y * VIDEO_MEM_COLS + cursor_pos_x;
    video_buffer[idx] = vm_vga_entry(c);
}

void vm_puts(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        vm_putch(data[i]);
    }
}

void vm_fg(VM_Color color)
{
    _attributes |= color;
}

void vm_bg(VM_Color color)
{
    _attributes |= color << 4;
}

void vm_newline()
{
    cursor_pos_x = 0;
    cursor_pos_y++;
}

void vm_cursor_pos(short x, short y)
{
    cursor_pos_x = x;
    cursor_pos_y = y;
}