#include <stdio.h>
//#include <freertos\FreeRTOS.h>
//#include <freertos\task.h>
#include "../include/Semaforo.h"

#define Delay 1000/portTICK_PERIOD_MS

void app_main()
{
    iniciarSemaforo();

    while (1)
    {
        actualizarSemaforo();
        vTaskDelay(Delay);
    }
    
}