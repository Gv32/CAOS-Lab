#include <stdint.h>
#include <stdio.h>
static uint32_t usart_is_tx_ready(void);
uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
void delay_routine_1(void);
void delay_routine_2(unsigned int delay_counter);