#include <stdio.h>
#include <freertos\FreeRTOS.h>
#include <freertos\task.h>
#include "../include/global.h"
#include "../include/pulsador.h"

void app_main()
{
    inicializarLed();
    iniciarPulsador(BOTON_A);
    iniciarPulsador(BOTON_B);

    while (1)
    {
        actualizarEstadoPulsador(BOTON_A);
        actualizarEstadoPulsador(BOTON_B);
    }
}