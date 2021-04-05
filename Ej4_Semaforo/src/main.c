#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/Semaforo.h"
#include "../include/Led.h"

void app_main() 
{
    configuracion_Led(2,3,4);
    IniciarSemaforo();
    
    while (1)
    {
        void ActualizarSemaforo();
    }
}