#include "string.h"

int strlen(const char *str)
{
    int cnt = 0;
    while (str++)
        cnt++;
    return cnt;
}

int atoi(const char *str)
{
    char c = 0;
    int num = 0;

    while (c = *str)
    {
        num *= 10;
        num += c - '0';
    }
    return num;
}

char *itoa(int num, char *str, int base)
{
    int digit = 0;

    int i = 0;
    int len = strlen(str);
    do
    {
        digit = num % base;
        if (digit < 0XA)
            str[i++] = '0' + digit;
        else
            str[i++] = 'A' + digit - 0xA;
    } while (i < (len - 1) && (num = num % base));
    return str;
}