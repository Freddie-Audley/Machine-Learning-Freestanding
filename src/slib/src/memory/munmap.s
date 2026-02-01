.section .text
    .global munmap
    .type munmap, @function

munmap:
    mov $11, %rax
    syscall
    ret
