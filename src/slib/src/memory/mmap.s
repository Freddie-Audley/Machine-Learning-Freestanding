.section .text
    .global mmap
    .type mmap, @function

mmap:
    mov $9, %rax
    syscall
    ret
