#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO GPIO_NUM_32

void app_main() 
{
    gpio_pad_select_gpio(BLINK_GPIO);

    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1)
    {
        /* code */
        printf("LED ON");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);

        printf("LED OFF");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);        
    }
    
}