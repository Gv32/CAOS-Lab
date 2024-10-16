#include "es3.h"
#include <stdio.h>

int main(void) {
    usart_init(); // Inizializza l'USART

    const uint8_t message[] = "Test!\n"; // Messaggio da inviare
    usart_tx_start(message, sizeof(message) - 1); // Invia il messaggio

    while (1); // Mantieni il programma in esecuzione
    return 0; // Non dovrebbe mai raggiungere questa linea
}
