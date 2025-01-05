#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5 // Maximum size of the buffer

int buffer[BUFFER_SIZE]; // Circular buffer to hold produced items
int in = 0; // Index for the next item to produce
int out = 0; // Index for the next item to consume

// Declare counting semaphores
SemaphoreHandle_t emptySlots;
SemaphoreHandle_t filledSlots;

// Producer task function
void producerTask(void *pvParameters) {
    while (1) {
        // Generate a random item as a string
        snprintf(buffer[in], ITEM_STRING_LENGTH, "Item %d", rand() % 100);

        // Wait for an empty slot
        xSemaphoreTake(emptySlots, portMAX_DELAY);

        // Add the item to the buffer
        printf("Produced: %s\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE; // Update index for next produced item

        // Signal that an item is available
        xSemaphoreGive(filledSlots);
        
        // Random delay to simulate variable production time
        vTaskDelay(pdMS_TO_TICKS(rand() % 200 + 100)); // Delay between 100 ms to 300 ms
    }
}

// Consumer task function
void consumerTask(void *pvParameters) {
    while (1) {
        // Wait for an available item
        xSemaphoreTake(filledSlots, portMAX_DELAY);

        // Consume the item from the buffer
        printf("Consumed: %s\n", buffer[out]);
        out = (out + 1) % BUFFER_SIZE; // Update index for next consumed item

        // Signal that a slot is free
        xSemaphoreGive(emptySlots);
        
        // Random delay to simulate variable consumption time
        vTaskDelay(pdMS_TO_TICKS(rand() % 300 + 100)); // Delay between 100 ms to 400 ms
    }
}

int main(void) {
    // Seed the random number generator
    srand(time(NULL));

    // Create counting semaphores
    emptySlots = xSemaphoreCreateCounting(BUFFER_SIZE, BUFFER_SIZE); // Initialize to the number of empty slots
    filledSlots = xSemaphoreCreateCounting(BUFFER_SIZE, 0); // Initialize to zero filled items

    // Create producer and consumer tasks
    xTaskCreate(producerTask, "Producer", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(consumerTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler(); // Start the FreeRTOS scheduler
    return 0; // Should never reach here
}
