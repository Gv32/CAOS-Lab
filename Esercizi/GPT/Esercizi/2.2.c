#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunctionA(void *pvParameters);
void vTaskFunctionB(void *pvParameters);

char log[1000];
int index;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

	SemaphoreHandle_t xSemaphore = xSemaphoreCreateBinary();

    UART_init();

	xTaskCreate(
		// Function which implements the task
		vTaskFunctionA,
		// Name of the task (debug purposes, not used by the kernel)
		"Task1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xSemaphore,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFunctionB,
		// Name of the task (debug purposes, not used by the kernel)
		"Task2",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xSemaphore,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

/* Task Function */
void vTaskFunctionA(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;
	SemaphoreHandle_t xSemaphore = pvParameters;

    for (;;) {

		xSemaphoreTake(xSemaphore, 100);

		int len = rand() % 26;
		int n = rand() % 4;
		char buffer [20];

		sprintf(buffer,"Task 1: ");
		for (int i = 0; i < (n+1); i++) {
			int len = rand() % 26;
			char c = 'a' + len;  // Carattere casuale tra 'a' e 'd'
			// Concatenare il carattere a buffer
			sprintf(buffer + strlen(buffer), "%c", c);  // Aggiungi il carattere alla fine
			sprintf(log + strlen(log), "%c", c);
		}
		sprintf(buffer + strlen(buffer), "\n");
		sprintf(log + strlen(log), " ");
		index = strlen(log);
		UART_printf(buffer);
		UART_printf("Buffer:\n");
		UART_printf(log);
		UART_printf("\n");

		xSemaphoreGive(xSemaphore);

		vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunctionB(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;
	SemaphoreHandle_t xSemaphore = pvParameters;

    for (;;) {

		xSemaphoreTake(xSemaphore, 100);
		int len = rand() % 26;
		int n = rand() % 4;
		char buffer [20];

		sprintf(buffer,"Task 2: ");
		for (int i = 0; i < (n+1); i++) {
			int len = rand() % 26;
			char c = 'a' + len;  // Carattere casuale tra 'a' e 'd'
			// Concatenare il carattere a buffer
			sprintf(buffer + strlen(buffer), "%c", c);  // Aggiungi il carattere alla fine
			sprintf(log + strlen(log), "%c", c);
		}
		sprintf(buffer + strlen(buffer), "\n");
		sprintf(log + strlen(log), " ");
		index = strlen(log);
		UART_printf(buffer);
		UART_printf("Buffer:\n");
		UART_printf(log);
		UART_printf("\n");
		xSemaphoreGive(xSemaphore);

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
