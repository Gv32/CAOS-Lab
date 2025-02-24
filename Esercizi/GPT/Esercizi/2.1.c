#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunctionA(void *pvParameters);
void vTaskFunctionB(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

	SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

    UART_init();

	xTaskCreate(
		// Function which implements the task
		vTaskFunctionA,
		// Name of the task (debug purposes, not used by the kernel)
		"Task1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xMutex,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFunctionB,
		// Name of the task (debug purposes, not used by the kernel)
		"Task1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xMutex,
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
	SemaphoreHandle_t xMutex = pvParameters;

    for (;;) {

		xSemaphoreTake(xMutex, 100);

        // Task code: print a message
        UART_printf("Mutex from Task 1\n");

		xSemaphoreGive(xMutex);

		vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunctionB(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;
	SemaphoreHandle_t xMutex = pvParameters;

    for (;;) {

		xSemaphoreTake(xMutex, 100);

        // Task code: print a message
        UART_printf("Mutex from Task 2\n");

		xSemaphoreGive(xMutex);

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
