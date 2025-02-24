/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"
#include "timers.h"

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */

#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )


/* GLOBAL VARIABLES */

TimerHandle_t timer1;
TimerHandle_t timer2;


static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}

void TaskA(){
    int cnt = 0;
    for(;;){
        cnt++;
        printf("Task A n: %d\n", cnt);
        vTaskDelay(1000);
    }
}

void Timer1(){
    printf("Hi I'm Timer 1\n");
}

void Timer2(){
    printf("GAME OVER\n");
}

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    //vInitialiseTimers();

    timer1 = xTimerCreate("Timer1",2000,pdTRUE,(void *) 0,Timer1);
    timer2 = xTimerCreate("Timer2",2000,pdFALSE,(void *) 1,Timer2);
    if(timer1 == NULL || timer2 == NULL){
        printf("Error in timer creartion\n");
    }
    xTimerStart(timer1,0);
    xTimerStart(timer2,0);

    xTaskCreate(TaskA,"TA",1000,NULL,1,NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}


