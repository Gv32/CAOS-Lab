#include "FreeRTOS.h"
#include "task.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask(void *pvParameters);

int main(int argc, char **argv){

    (void) argc;
    (void) argv;

    UART_init();

    xTaskCreate(vTask,"task_Main", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL);

    vTaskStartScheduler();

}

void vTask(void *param){

    (void) param;

    for(;;){
        xTaskCreate(vTask1,"T1", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL);
        xTaskCreate(vTask2,"T2", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL);
    }
    vTaskDelete(NULL);
}

void vTask1(void *param){

	(void) param;
    UART_printf("Hello, World from task 1!\n");
    vTaskDelete(NULL);
}

void vTask2(void *param){

	(void) param;
    UART_printf("Hello, World from task 2!\n");
    vTaskDelete(NULL);
}