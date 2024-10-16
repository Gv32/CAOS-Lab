#include "delay.h"

void delay_routine_1(void){
    asm(
        "mov R1, #10\n"
        "loop:\n"
            "subs R1, R1, #1\n"
            "cmp R1, #0\n"
        "bne loop\n"
    );
}