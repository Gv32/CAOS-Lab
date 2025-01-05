#include "FreeRTOS.h"
#include "task.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction(void *pvParameters);
void vTaskFunction2(void *pvParameters);
void vTaskFib(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

	//xTaskCreate(
		// Function which implements the task
	//	vTaskFunction,
		// Name of the task (debug purposes, not used by the kernel)
	//	"Task1",
		// Stack to allocate to the task
	//	configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
	//	NULL,
		// Priority assigned to the task
	//	mainTASK_PRIORITY,
		// Task handle. Not required
	//	NULL
	//);

	//xTaskCreate(
		// Function which implements the task
	//	vTaskFunction2,
		// Name of the task (debug purposes, not used by the kernel)
	//	"Task2",
		// Stack to allocate to the task
	//	configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
	//	NULL,
		// Priority assigned to the task
	//	mainTASK_PRIORITY,
		// Task handle. Not required
	//	NULL
	//);

	xTaskCreate(
		// Function which implements the task
		vTaskFib,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskFib1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		NULL,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFib,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskFib2",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		NULL,
		// Priority assigned to the task
		mainTASK_PRIORITY-1,
		// Task handle. Not required
		NULL
		
	);
	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

/* Task Function */
void vTaskFunction(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

    for (;;) {

        // Task code: print a message
        UART_printf("Hello, World!\n");

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunction2(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

    for (;;) {

        // Task code: print a message
        UART_printf("Hello, World from task 2!\n");

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFib(void *pvParameters) {
    // Avoid warning about unused pvParameters
    (void) pvParameters;

    int n1 = 0;
    int n2 = 1;
    int n3 = 0;
    char buffer[50];  // Buffer per la stringa

    // Funzione interna per convertire int a stringa
    void intToStr(int num, char *str) {
        int i = 0;
        if (num == 0) {
            str[i++] = '0';
        } else {
            if (num < 0) {
                str[i++] = '-';
                num = -num;
            }
            int j = i;
            while (num > 0) {
                str[j++] = (num % 10) + '0';
                num /= 10;
            }
            // Inverti la stringa
            for (int k = i, l = j - 1; k < l; k++, l--) {
                char temp = str[k];
                str[k] = str[l];
                str[l] = temp;
            }
            i = j; // Aggiorna la lunghezza della stringa
        }
        str[i] = '\0'; // Termina la stringa
    }

    // Stampa il valore iniziale di n1
    intToStr(n1, buffer);
    UART_printf(buffer);
    UART_printf("\n");  // Aggiungi nuova riga

    // Stampa il valore iniziale di n2
    intToStr(n2, buffer);
    UART_printf(buffer);
    UART_printf("\n");  // Aggiungi nuova riga

    // Calcolo della sequenza di Fibonacci
    for (int i = 0; i < 10; i++) {
        n3 = n2 + n1;
        n1 = n2;
        n2 = n3;

        // Stampa il valore di n3
        intToStr(n3, buffer);
        UART_printf(buffer);
        UART_printf("\n");  // Aggiungi nuova riga
    }
	vTaskDelete(NULL);
}

