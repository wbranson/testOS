#include "vidmem.h"
#include "lib/string.h"

static VM_Color term_fg_color = White;
static VM_Color term_bg_color = Black;

static const char **buffer;

void term_init()
{
    vm_bg(term_bg_color);
    vm_fg(term_fg_color);
}

void term_putc(char c)
{
    if (c == '\n')
        vm_newline();
    else
        vm_putch(c);
}
void term_write(const char *str)
{
    if (str == NULL)
        return;
    if (*str == 0)
        return;

    do
    {
        if (*str == '\n')
            vm_newline();
        else
            vm_putch(*str);
    } while (*(++str) != 0);
}

void term_background(VM_Color color)
{
    term_bg_color = color;
}

void term_foreground(VM_Color color)
{
    term_fg_color = color;
}