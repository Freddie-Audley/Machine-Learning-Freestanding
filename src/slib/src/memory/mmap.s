.section .text
    .global mmap
    .type mmap, @function

mmap:
    mov %rcx, %r10
    mov $9, %rax
    syscall
    ret
