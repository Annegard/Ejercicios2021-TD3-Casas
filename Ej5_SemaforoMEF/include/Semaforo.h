#ifndef Semaforo_H_
#define Semaforo_H_

    //librerias
    #include <freertos\FreeRTOS.h>
    #include <freertos\task.h>
    #include "driver/gpio.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    //definiciones
    #define ledROJO        GPIO_NUM_6  // GPIO conectado al LED
    #define ledAMARILLO    GPIO_NUM_7
    #define ledVERDE       GPIO_NUM_8
    //variables
    //tipo de datos para la variable de estados
    typedef enum
    {
        ROJO,
        ROJO_AMARILLO,
        VERDE,
        AMARILLO
    }estadoMEF_t;
    //variable de estado (global)
    estadoMEF_t estadoActual;
    int contador;
    //funciones
    void iniciarSemaforo();
    void actualizarSemaforo();
    void apagarLed();

#endif