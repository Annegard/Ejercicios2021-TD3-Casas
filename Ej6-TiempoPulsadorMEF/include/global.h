#ifndef global_H_
#define global_H_

    #include <freertos\FreeRTOS.h>
    #include <freertos\task.h>
    #include "driver/gpio.h"

    #define LED1 GPIO_NUM_6  // GPIO conectado al LED
    #define LED2 GPIO_NUM_7
    #define LED3 GPIO_NUM_8

    #define BOTON_A GPIO_NUM_33 // conectar el interruptor de contacto GPIO
    #define BOTON_B GPIO_NUM_32

    #define retardo 5

#endif