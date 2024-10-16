#include "es3.h"

int main(void) {
    const uint8_t message_success[] = "Transmission successful!\n";
    const uint8_t message_error[] = "Error: No data to transmit.\n";
    const uint8_t message_busy[] = "Error: Transmission is busy.\n";
    const uint8_t message_incomplete[] = "Error: Transmission incomplete due to early null-terminator.\n";
    
    const uint8_t message_to_send[] = "Hello, USART!"; // Messaggio da inviare
    uint32_t result = usart_tx_start(message_to_send, sizeof(message_to_send) - 1); // -1 per escludere il terminatore nullo

    // Gestisci il risultato
    if (result == 3) {
        usart_tx_start(message_success, sizeof(message_success) - 1);
    } else if (result == 0) {
        usart_tx_start(message_error, sizeof(message_error) - 1);
    } else if (result == 1) {
        usart_tx_start(message_busy, sizeof(message_busy) - 1);
    } else if (result == 2) {
        usart_tx_start(message_incomplete, sizeof(message_incomplete) - 1);
    }

    // Aggiungi eventuali ritardi o altre logiche
    return 0;
}
