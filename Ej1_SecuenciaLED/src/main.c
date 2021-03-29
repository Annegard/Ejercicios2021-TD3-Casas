#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BOTON_A GPIO_NUM_32
#define BOTON_B GPIO_NUM_32

void app_main() 
{
    gpio_pad_select_gpio(BOTON_A);
    gpio_pad_select_gpio(BOTON_B);
    
    gpio_set_direction(BOTON_A, GPIO_MODE_INPUT);

    while (1)
    {
        /* code */
        printf("LED ON");
        gpio_set_level(BOTON_A, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);

        printf("LED OFF");
        gpio_set_level(BOTON_A, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);        
    }
    
}