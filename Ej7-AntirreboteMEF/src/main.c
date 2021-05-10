#include "../include/global.h"
#include "../include/pulsador.h"
#include "../include/led.h"


void app_main()
{
    inicializarLed(ledROJO, ledAMARILLO, ledVERDE);
    iniciarPulsador(BOTON_A);

    while (1)
    {
        actualizarEstadoPulsador(BOTON_A);
    }
}