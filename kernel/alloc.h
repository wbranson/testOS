#ifndef __ALLOC_H
#define __ALLOC_H
#include <stddef.h>

void *kmalloc(size_t size);
void *kmemset(void *ptr, int value, size_t size);
#endif