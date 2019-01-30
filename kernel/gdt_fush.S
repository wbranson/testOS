.global gdt_flush
.type gdt_flush, @function
gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    
    //Load GDT data segment offset into selctor registers
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    //Set CS to 0x08, index of our code selector
    ljmp    $0x08, $.flush 

.flush:
    ret