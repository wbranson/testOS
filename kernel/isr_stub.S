.macro ISR num
    .global isr_\num
    isr_\num:
        cli  
        push $0 
        push $\num
        jmp isr_common
.endm

.macro ISR_ERR num
    .global isr_\num
    isr_\num:
        cli
        push $\num
        jmp isr_common
.endm

.macro IRQ irq_n, isr_n
    .global irq_\irq_n
    irq_\irq_n:
        cli
        push $0
        push $\isr_n
        jmp irq_common
.endm

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR_ERR 8
ISR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31
ISR 32
ISR 33
ISR 34
ISR 35
ISR 36
ISR 37
ISR 38
ISR 39
ISR 40
ISR 41
ISR 42
ISR 43
ISR 44
ISR 45
ISR 46
ISR 47
ISR 128


IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

isr_common:
    pusha

    mov %ds, %ax    /* Lower 16-bits of EAX = DS */
    push %eax       /* Save DS (data descriptor) */

    mov $0x10, %ax  /* Load the kernel DS */
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    //push %esp

    call isr_handler

    //add $4, %esp

    pop %ebx        /* Reload original DS */
    mov %bx, %ds
    mov %bx, %es
    mov %bx, %fs
    mov %bx, %gs

    popa
    add $8, %esp
    sti
    iret


irq_common:
    pusha
    
    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call irq_handler

    pop %ebx
    mov %bx, %ds
    mov %bx, %es
    mov %bx, %fs
    mov %bx, %gs

    popa
    add $8, %esp
    sti
    iret


.global pic_eoi
pic_eoi:
    mov $0x20, %eax
    mov 4(%esp), %ecx
    cmp $39, %ecx
    jle 1f
    mov $0xA0, %edx
    outb %al, %dx
1:  mov $0x20, %edx
    outb %al, %dx
    ret


