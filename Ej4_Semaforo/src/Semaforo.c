#include "../include/Semaforo.h"
#include "../include/Led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define Delay 10

void IniciarSemaforo()
{

}
void ActualizarSemaforo()
{
    vTaskDelay(Delay);
}
