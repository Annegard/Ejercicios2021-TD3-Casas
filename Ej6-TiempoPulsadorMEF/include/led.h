#ifndef led_H_
#define led_H_

    #include "../include/global.h"

    void inicializarLed(gpio_int_type_t Led1, gpio_int_type_t Led2, gpio_int_type_t Led3);
    void Secuencia(gpio_int_type_t Sentido);
    void ledOFF();
#endif