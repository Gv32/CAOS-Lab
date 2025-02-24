/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */

#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )


/* GLOBAL VARIABLES */

SemaphoreHandle_t semA;
SemaphoreHandle_t semBC;
SemaphoreHandle_t semD;


static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}

void TaskA(){
    for(;;){
        xSemaphoreTake(semA,portMAX_DELAY);
        printf("Hi, I'm Task A\n");
        xSemaphoreGive(semBC);
    }
}

void TaskB(){
    for(;;){
        xSemaphoreTake(semBC,portMAX_DELAY);
        printf("Hi, I'm Task B\n");
        xSemaphoreGive(semD);
    }
}

void TaskC(){
    for(;;){
        xSemaphoreTake(semBC,portMAX_DELAY);
        printf("Hi, I'm Task C\n");
        xSemaphoreGive(semD);
    }
}

void TaskD(){
    for(;;){
        xSemaphoreTake(semD,portMAX_DELAY);
        printf("Hi, I'm Task D\n\n");
        vTaskDelay(500);
        xSemaphoreGive(semA);
    }
}

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    //vInitialiseTimers();

    semA = xSemaphoreCreateCounting(1,1);
    semBC = xSemaphoreCreateCounting(1,0);
    semD = xSemaphoreCreateCounting(1,0);

    xTaskCreate(TaskA,"TA",1000,NULL,1,NULL);
    xTaskCreate(TaskB,"TB",1000,NULL,1,NULL);
    xTaskCreate(TaskC,"TC",1000,NULL,1,NULL);
    xTaskCreate(TaskD,"TD",1000,NULL,1,NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}


