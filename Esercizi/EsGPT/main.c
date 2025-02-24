#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "uart.h"
#include "timers.h"

TimerHandle_t timer = NULL;

int cnt = 0;

void handler(void *pvParameters){
    cnt = cnt + 1;
    UART_printf(cnt);
    UART_printf('\n');
}

int main(void) {
    
    UART_init();

    timer = xTimerCreate("Timer", pdMS_TO_TICKS(2000), pdTRUE, (void*) 0,handler);
    if(timer!=NULL){
        xTimerStart(timer,0);
    }
    vTaskStartScheduler(); // Start the FreeRTOS scheduler
    return 0; // Should never reach here
}
