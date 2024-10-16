#ifndef ES3_H
#define ES3_H

#include <stdint.h>
#include <stddef.h>

#define USART1_BASE (0x40011000)

typedef struct {
    volatile uint32_t status_reg; // Registro di stato
    volatile uint32_t data_reg;   // Registro dati
} usart1_t;

#define usart ((usart1_t *) USART1_BASE)

enum {
    USART_TX_ERROR,
    USART_TX_BUSY,
    USART_TX_INCOMPLETE,
    USART_TX_COMPLETE,
};

void usart_init(void); // Rimuovi static
uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
void delay_routine_1(void);
void delay_routine_2(unsigned int delay_counter);

#endif // ES3_H
