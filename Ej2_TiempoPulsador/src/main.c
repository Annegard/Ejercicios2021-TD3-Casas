#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define ESP_INTR_FLAG_DEFAULT 0

#define BOTON_A GPIO_NUM_33 // conectar el interruptor de contacto GPIO
#define BOTON_B GPIO_NUM_32
#define LED_A    GPIO_NUM_6  // GPIO conectado al LED
#define LED_B    GPIO_NUM_7

int delay = 1;
int TIEMPO_A=0;
int TIEMPO_B=0;

void setup();
void gpio_isr_handler();

void app_main(void)
{
    setup();

    while (1)
    {
        gpio_set_level(LED_A,0);
        gpio_set_level(LED_B,0);
        
        while (TIEMPO_A || TIEMPO_B)
        {
            if (TIEMPO_A > 0)
            {
                gpio_set_level(LED_A,1);
                TIEMPO_A--;
            }
            else
            {
                gpio_set_level(LED_A,0);
            }

            if (TIEMPO_B > 0)
            {
                gpio_set_level(LED_B,1);
                TIEMPO_B--;
            }
            else
            {
                gpio_set_level(LED_B,0);
            }
        }
    }
}

void setup()
{
    // Configura el GPIO que controla el LED al modo de salida
    gpio_set_direction(LED_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_B, GPIO_MODE_OUTPUT);

    // Establece el pin GPIO como interrupción en el modo de salida
    gpio_set_direction(BOTON_A, GPIO_MODE_INPUT);
    gpio_set_direction(BOTON_B, GPIO_MODE_INPUT);

    // Establece el modo de interrupción como disparador de flanco ascendente
    gpio_set_intr_type(BOTON_A, GPIO_INTR_POSEDGE);
    gpio_set_intr_type(BOTON_B, GPIO_INTR_POSEDGE);

    // Inicializa la rutina del servicio de interrupción del GPIO global y establece el nivel de interrupción
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    // Monta el GPIO especificado en el servicio de interrupción y configura la función de devolución de
    //llamada y los parámetros entrantes activados por la interrupción
    gpio_isr_handler_add(BOTON_A, gpio_isr_handler, (void*)BOTON_A);
    gpio_isr_handler_add(BOTON_B, gpio_isr_handler, (void*)BOTON_B);
}

void gpio_isr_handler()
{
    if (gpio_get_level(BOTON_A))
    {
        while (gpio_get_level(BOTON_A))
        {
            vTaskDelay(delay/portTICK_PERIOD_MS);
            TIEMPO_A++;
        }
    }
    else if (gpio_get_level(BOTON_B))
    {
        while (gpio_get_level(BOTON_B))
        {
            vTaskDelay(delay/portTICK_PERIOD_MS);
            TIEMPO_B++;
        }
    }
    else
    {
        printf("FIJATE QUE TE ESTAS MANDANDO CAGADA 1\n");
    }
}