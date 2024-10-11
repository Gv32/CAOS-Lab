.section .data
    array:  .word 1, 2, 3, 4, 5
    dim:    .word 5
.section .text
.global _start

_start:
    ldr R0, =array
    mov R1, #5

    bl reverse

    b .

reverse:
    mov R2, #4      // Index from the end
    mov R3, #0      // Index from the start
    loop:
        ldr R4, [R0, R2, lsl #2]    // Read an element from the end
        ldr R5, [R0, R3, lsl #2]    // Read an element from the start
        str R4, [R0, R3, lsl #2]    // Store the last element a the start
        str R5, [R0, R2, lsl #2]    // Store the first element a the end
        add R3, R3, #1
        sub R2, R2, #1
        cmp R2, R3
        bge loop                         
    bx LR
    