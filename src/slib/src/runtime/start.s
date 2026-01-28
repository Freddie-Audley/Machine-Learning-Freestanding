.section .text
    .global _start
    .type _start, @function

_start:
    call main

    mov %eax, %edi
    mov $60, %rax
    syscall
