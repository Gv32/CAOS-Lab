.section .data
    num: .word 31
.section .text
.global _start

_start:
    ldr R0, =num
    ldr R1, [R0]
    bl count
    b .

count:
    mov R2, #0 //counter
    loop:
        tst R1, #1
        addne R2, R2, #1
        lsr R1, R1, #1
        cmp R1, #0
        bne loop
    mov R0, R2
    bx LR
