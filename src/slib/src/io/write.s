.section .text
    .global write
    .type write, @function

write:
    mov $1, %rax
    syscall
    ret
