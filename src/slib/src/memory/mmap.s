.section .text
    .global mmap
    .type mmap, @function

mmap:
    mov $9, %rax
    mov %rcx, %r10
    syscall
    ret
