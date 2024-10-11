//Esercizio 1
//Sums the first 30 numbers and save the result in the r1 register
.section .data
.section .text
.word stack_top     // Address of the stack_top
.word _start        // Address of the _start function
.thumb_func

.global _start
_start:
    mov r1, #0      // Initialize the counter to 0
    mov r0, #0      // Initialize the index to 0

loop:
    add r1, r1, r0  // sum = sum + index
    add r0, r0, #1  // index++
    cmp r0, #31     // if index < 31
    blt loop        // jump to loop

end:
    b .
