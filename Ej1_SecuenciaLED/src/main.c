#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define ESP_INTR_FLAG_DEFAULT 0

#define BOTON_A GPIO_NUM_33 // conectar el interruptor de contacto GPIO
#define BOTON_B GPIO_NUM_32
#define LED1    GPIO_NUM_6  // GPIO conectado al LED
#define LED2    GPIO_NUM_7
#define LED3    GPIO_NUM_8

int delay = 1000;

void Secuencia_1();
void Secuencia_2();
void setup();
void gpio_isr_handler();

void app_main(void)
{
    setup();

    while (1)
    {
        //code
    }
}

void setup()
{
    // Configura el GPIO que controla el LED al modo de salida
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

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
     printf("INTERRUPCION EJECUTADA\n");
    if (gpio_get_level(BOTON_A) == 1)
    {
        Secuencia_1();
    }
    else if (gpio_get_level(BOTON_B) == 1)
    {
        Secuencia_2();
    }
    else
    {
        printf("SALTO CUALQUIER COSA, O TAL VEZ LOS DOS, NI IDEA, LA CUESTION ES QUE CAGASTE\n");
    }
}

void Secuencia_1()
{
    printf("SECUENCIA 1\n");
    gpio_set_level(LED1,1);
    gpio_set_level(LED2,0);
    gpio_set_level(LED3,0);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    gpio_set_level(LED1,0);
    gpio_set_level(LED2,1);
    gpio_set_level(LED3,0);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    gpio_set_level(LED1,0);
    gpio_set_level(LED2,0);
    gpio_set_level(LED3,1);
    vTaskDelay(delay/portTICK_PERIOD_MS); 
}

void Secuencia_2()
{
    printf("SECUENCIA 2\n");
    gpio_set_level(LED1,0);
    gpio_set_level(LED2,0);
    gpio_set_level(LED3,1);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    gpio_set_level(LED1,0);
    gpio_set_level(LED2,1);
    gpio_set_level(LED3,0);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    gpio_set_level(LED1,1);
    gpio_set_level(LED2,0);
    gpio_set_level(LED3,0);
    vTaskDelay(delay/portTICK_PERIOD_MS);  
}