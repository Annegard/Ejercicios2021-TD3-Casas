#include "../include/global.h"
#include "../include/pulsador.h"
#include "../include/led.h"
#include <freertos\FreeRTOS.h>
#include <freertos\task.h>
#include "driver/gpio.h"

void app_main()
{
    inicializarLed(LED1, LED2, LED3);
    iniciarPulsador(BOTON_A);
    iniciarPulsador(BOTON_B);

    while (1)
    {
        actualizarEstadoPulsador(BOTON_A);
        actualizarEstadoPulsador(BOTON_B);
    }
}