.section .data
.section .text
.global _start

_start:
    mov R0, #10
    bl fibonacci
    b .

fibonacci:
    mov R1, #0
    mov R2, #1
    mov R3, #2
    loop:
        add R4, R1, R2
        mov R1, R2
        mov R2, R4
        add R3, #1
        cmp R3, #10
        bne loop
    bx LR