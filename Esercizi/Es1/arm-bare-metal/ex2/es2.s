//Esercizio 2
//Sum of Array using ARMv7 Assembly
.section .data
    array: .word 1, 2, 3, 4, 5
.section .text
.global _start
.syntax unified

_start:
    ldr R0, =array  // Load array addres to R0
    mov R1, #5      // Load the length of the array in R1

    bl sum
    
    b .

sum:
    mov R2, #0      // Sum counter
    mov R3, #0      // Index
sum_loop:
    ldr R4, [R0, R3, LSL #2]
    add R2, R2, R4
    add R3, R3, #1
    cmp R3, R1
    bne sum_loop
    bx LR
