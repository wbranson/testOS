#include "multiboot.h"

typedef int (*initcall_t)(void);
#define __section(S) __attribute__((__section__(#S)))
#define __used __attribute__((__used__))
#define __init __section(.init)

static int __init myFunc(void)
{
    for (int i = 0; i < 3; i++)
        ;
    return 0;
}

void kernel_main(multiboot_info_t *mbd, unsigned int magic)
{
    magic = magic;
    mbd = mbd;

    while (1)
        ;
}

static __used initcall_t __initcall_myFunc6 __section(".initcall6.init") = myFunc;
