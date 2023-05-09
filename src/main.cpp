#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "main.pio.h"

volatile QueueHandle_t queue = NULL;
const TickType_t ms_delay = 500 / portTICK_PERIOD_MS;
uint sm_0;
uint sm_1;

void task_0(__attribute__((unused)) void* arg) {
    // Simple example of inter-task communication.
    uint8_t state = 0;
    for(;;) {
        state = 1;
        pio_sm_put_blocking(pio0, sm_0, state);
        xQueueSendToBack(queue, &state, 0);
        vTaskDelay(ms_delay);

        state = 0;
        pio_sm_put_blocking(pio0, sm_0, state);
        xQueueSendToBack(queue, &state, 0);
        vTaskDelay(ms_delay);
    }
}

void task_1(__attribute__((unused)) void* arg) {
    // Simple example of inter-task communication.
    uint8_t state = 0;
    for(;;) {
        if(xQueueReceive(queue, &state, portMAX_DELAY) == pdTRUE) pio_sm_put_blocking(pio0, sm_1, ~state);
    }
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
    stdio_init_all();

    // Setup the pio for the tasks.
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &main_program);
    sm_0 = pio_claim_unused_sm(pio, true);
    sm_1 = pio_claim_unused_sm(pio, true);
    main_program_init(pio, sm_0, offset, 25);
    main_program_init(pio, sm_1, offset, 10);

    // Two example tasks.
    xTaskCreate(task_0, "TASK_0", 128, NULL, 1, NULL);
    xTaskCreate(task_1, "TASK_1", 128, NULL, 1, NULL);

    // Create an event queue.
    queue = xQueueCreate(4, sizeof(uint8_t));

    // Start the scheduler.
    vTaskStartScheduler();

    for(;;) tight_loop_contents();
}
