#ifndef global_H_
#define global_H_

    #include <freertos\FreeRTOS.h>
    #include <freertos\task.h>
    #include "driver/gpio.h"

    #define ledROJO GPIO_NUM_6  // GPIO conectado al LED
    #define ledAMARILLO GPIO_NUM_7
    #define ledVERDE GPIO_NUM_8

    #define BOTON_A GPIO_NUM_33 // conectar el interruptor de contacto GPIO
    #define BOTON_B GPIO_NUM_32

    #define retardo 5
    
    unsigned long millis();
#endif