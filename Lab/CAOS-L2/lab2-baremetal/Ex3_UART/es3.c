#include "es3.h"
#include <stdint.h>
#include <stdio.h>
enum {
    USART_TX_ERROR,
    USART_TX_BUSY,
    USART_TX_INCOMPLETE,
    USART_TX_COMPLETE,
};

typedef struct {
    volatile unsigned int data_reg;   // Usare volatile per garantire che il compilatore non ottimizzi gli accessi
    volatile unsigned int status_reg; // Usare volatile per garantire che il compilatore non ottimizzi gli accessi
} usart1_t;

const uint32_t TIMEOUT = 10;
usart1_t usart; // Simulazione della struttura USART

static uint32_t usart_is_tx_ready(void) {
    // Controlla il bit 7 del status_reg per la prontezza del buffer
    return (usart.status_reg & 0x80) ? 1 : 0;
}

uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes) {
    if (data_bytes == NULL) {
        return USART_TX_ERROR; // Nessun dato da inviare
    }

    for (uint32_t i = 0; i < n_bytes; i++) {
        uint32_t timeout = TIMEOUT;

        // Aspetta che il buffer sia pronto
        while (!usart_is_tx_ready()) {
            if (timeout-- == 0) {
                return USART_TX_BUSY; // Timeout
            }
        }

        usart.data_reg = data_bytes[i]; // Invia il byte corrente

        // Controlla se il prossimo byte è un terminatore nullo
        if (i < n_bytes - 1 && data_bytes[i + 1] == '\0') {
            return USART_TX_INCOMPLETE; // Trasmissione incompleta
        }
    }

    return USART_TX_COMPLETE; // Trasmissione completata
}

void delay_routine_1(void) {
    __asm(
        "mov r1, #11 \n"
        "loop: \n"
        "sub r1, r1, #1 \n"
        "cmp r1, #0 \n"
        "bne loop \n"
    );
}

void delay_routine_2(unsigned int delay_counter) {
    __asm(
        "mov r0, %0 \n"
        "loop2: \n"
        "sub r0, r0, #1 \n"
        "cmp r0, #0 \n"
        "bne loop2 \n"
        : // No output
        : "r" (delay_counter) // Input: delay_counter
    );
}
