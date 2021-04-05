#include "../include/Led.h"
#include "driver/gpio.h"

void configuracion_Led(int LED_1, int LED_2, int LED_3)
{
    gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_3, GPIO_MODE_OUTPUT);
}