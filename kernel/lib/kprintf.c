#include <stdarg.h>
#include "../alloc.h"
#include "../terminal.h"
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define FLG_LEFTALIGN (1U << 0U)
#define FLG_SHOWSIGN (1U << 1U)
#define FLG_SIGNED (1U << 2U)
#define FLG_ZERO (1U << 3U)
#define FLG_ALT (1U << 4U)
#define FLG_CHAR (1U << 5U)
#define FLG_SHORT (1U << 6U)
#define FLG_LONG (1U << 7U)
#define FLG_LONG_LONG (1U << 8U)

static int _parse_length(const char **fmt)
{
    int flg = 0;
    switch (**fmt)
    {
    case 'h':
        flg = FLG_SHORT;
        (*fmt)++;
        if ((**fmt) == 'h')
        {
            flg = FLG_CHAR;
            (*fmt)++;
        }
        break;
    case 'l':
        flg = FLG_LONG;
        (*fmt)++;
        if (**fmt == 'l')
        {
            flg = FLG_LONG_LONG;
            (*fmt)++;
        }
        break;
    case 'j':
        flg = (sizeof(intmax_t) == sizeof(long)) ? FLG_LONG : FLG_LONG_LONG;
        (*fmt)++;
        break;
    case 'z':
        flg = (sizeof(size_t) == sizeof(long)) ? FLG_LONG : FLG_LONG_LONG;
        (*fmt)++;
        break;
    case 't':
        flg = (sizeof(ptrdiff_t) == sizeof(long)) ? FLG_LONG : FLG_LONG_LONG;
        (*fmt)++;
        break;
    default:
        break;
    }
    return flg;
}
static int _parse_flags(const char **fmt)
{
    char c;

    int flags = 0;
    while ((c = **fmt) && (c == '-' || c == '+' || c == '0' || c == '#'))
    {
        switch (c)
        {
        case '-':
            flags |= FLG_LEFTALIGN;
            break;
        case '+':
            flags |= FLG_SHOWSIGN;
            break;
        case '0':
            flags |= FLG_ZERO;

            break;
        case '#':
            flags |= FLG_ALT;
            break;
        }
        (*fmt)++;
    }
    return flags;
}

static int _parse_width(const char **fmt, va_list *ap)
{
    char c = **fmt;
    int num = 0;

    if (c == '*')
    {
        return va_arg(*ap, int);
    }

    while ((c = **fmt) && (c >= '0' && c <= '9'))
    {
        num *= 10;
        num += c - '0';
        (*fmt)++;
    }

    return num;
}

static int _parse_precision(const char **fmt, va_list *ap)
{
    char c;
    int num = 0;
    if (**fmt != '.')
        return 0;

    (*fmt)++;

    if (**fmt == '*')
    {
        return va_arg(*ap, int);
    }

    while ((c = **fmt) && (c >= '0' && c <= '9'))
    {
        num *= 10;
        num += c - '0';
        (*fmt)++;
    }
    return num;
}

static int _write_itoa(unsigned int val,
                       int flags,
                       int width,
                       int precision)
{
    int i = 0, cnt = 0;
    int neg = (int)val > 0 ? 1 : -1;

    char buffer[15];
    kmemset(&buffer, 0, 15);
    if (neg < 0)
        val = -val;

    do
    {
        buffer[i++] = '0' + val % 10;
    } while (((val = val / 10) > 0) && i < 15);

    if (!(flags & FLG_LEFTALIGN))
    {
        if ((flags & FLG_ZERO))
        {
            if ((flags & FLG_SHOWSIGN) && (neg > 0))
            {
                term_putc('+');
                cnt++;
            }

            if (neg < 0)
            {
                term_putc('-');
                cnt++;
            }
        }
        int pad = width - (i + ((flags & FLG_SHOWSIGN) ? 1 : 0));
        while (pad-- > 0)
        {
            cnt++;
            term_putc((flags & FLG_ZERO) ? '0' : ' ');
        }
        if (!(flags & FLG_ZERO))
        {
            if ((flags & FLG_SHOWSIGN) && (neg > 0))
            {
                term_putc('+');
                cnt++;
            }

            if (neg < 0)
            {
                term_putc('-');
                cnt++;
            }
        }
    }
    else
    {
        if ((flags & FLG_SHOWSIGN) && (neg > 0))
        {
            term_putc('+');
            cnt++;
        }

        if (neg < 0)
        {
            term_putc('-');
            cnt++;
        }
    }

    while (--i >= 0)
    {
        cnt++;
        term_putc(buffer[i]);
    }

    if (flags & FLG_LEFTALIGN)
    {
        while (cnt++ < width)
        {
            term_putc(' ');
        }
    }
    return cnt;
}

static int _write(int flags,
                  int width,
                  int precision,
                  int length,
                  char type,
                  va_list *ap)
{
    switch (type)
    {
    case 's':
    {
        char *str = va_arg(*ap, char *);
        int cnt = 0;
        char c;
        while ((c = *str++))
        {
            cnt++;
            term_putc(c);
        }
        return cnt;
    }
    case 'c':
    {
        switch (length)
        {
        case 0:
        {
            int c = va_arg(*ap, int);
            term_putc(c);
            return 1;
        }
        }
        return 0;
    }
    case 'd':
    case 'i':
    {
        switch (length)
        {
            //TODO: Lengths > 32 bit are not supported at this time.  Missing __umoddi3 and __udivdi3.
            //Since this is just the kernel printf, we may never implement this as long as we are only
            //a 32 bit OS.
        default:
        {
            int c = va_arg(*ap, int);
            return _write_itoa(c, flags, width, precision);
        }
        }
        break;
    }
    case 'u':
    {
        unsigned int c = va_arg(*ap, unsigned int);
        return _write_itoa(c, flags, width, precision);
    }
    case 'o':
    case 'x':
    case 'X':
        break;
    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'a':
    case 'A':
        break;
    }
    return 0;
}
static int _kprintf(const char *fmt, va_list *ap)
{
    char c;
    int flags = 0;
    int width = 0;
    int precision = 0;
    int cnt = 0;
    int length = 0;

    while ((c = *fmt++) != 0)
    {
        if (c != '%')
        {
            cnt++;
            term_putc(c);
        }
        else
        {
            if (*fmt == '%')
            {
                term_putc(*fmt);
                continue;
            }

            flags = _parse_flags(&fmt);
            width = _parse_width(&fmt, ap);
            precision = _parse_precision(&fmt, ap);
            length = _parse_length(&fmt);
            _write(flags, width, precision, length, *fmt++, ap);
        }
    }
    return cnt;
}

int kprintf(const char *fmt, ...)
{
    int cnt;
    va_list ap;
    va_start(ap, fmt);
    cnt = _kprintf(fmt, &ap);
    va_end(ap);
    return cnt;
}