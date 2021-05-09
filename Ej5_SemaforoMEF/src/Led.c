#include "../include/Led.h"

void setLED(){
    gpio_set_direction(ledROJO,     GPIO_MODE_OUTPUT);
    gpio_set_direction(ledAMARILLO, GPIO_MODE_OUTPUT);
    gpio_set_direction(ledVERDE,    GPIO_MODE_OUTPUT);
}

void prenderLed(int num){

    switch (num)
    {
    case 0://rojo
        gpio_set_level(ledROJO,     1);
        gpio_set_level(ledAMARILLO, 0);
        gpio_set_level(ledVERDE,    0);
        break;
    case 1://rojo_amarillo
        gpio_set_level(ledROJO,     1);
        gpio_set_level(ledAMARILLO, 1);
        gpio_set_level(ledVERDE,    0);
        break;
    case 2://rojo
        gpio_set_level(ledROJO,     0);
        gpio_set_level(ledAMARILLO, 0);
        gpio_set_level(ledVERDE,    1);
        break;
    case 3://rojo
        gpio_set_level(ledROJO,     0);
        gpio_set_level(ledAMARILLO, 1);
        gpio_set_level(ledVERDE,    0);
        break;
    
    default:
        break;
    }
    
}


//funcion que apaga todos los leds
void apagarLed(){
    gpio_set_level(ledROJO,     0);
    gpio_set_level(ledAMARILLO, 0);
    gpio_set_level(ledVERDE,    0);
}
