#include "../include/global.h"
#include "../include/Led.h"
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