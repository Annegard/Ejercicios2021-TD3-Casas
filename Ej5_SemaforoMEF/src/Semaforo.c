#include "../include/Semaforo.h"

void iniciarSemaforo()
{
    gpio_set_direction(ledROJO,     GPIO_MODE_OUTPUT);
    gpio_set_direction(ledAMARILLO, GPIO_MODE_OUTPUT);
    gpio_set_direction(ledVERDE,    GPIO_MODE_OUTPUT);

    contador=0;
    estadoActual = ROJO;
}

void actualizarSemaforo()
{
    switch (estadoActual)
    {
        case ROJO:
        {
            if (contador==0)
            {
                apagarLed();//apagar todos los leds
                gpio_set_level(ledROJO,     1);
            }
            if (contador == 60)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoActual = ROJO_AMARILLO;
            }
            contador ++;
        }    
        break;
        case ROJO_AMARILLO:
        {
            if (contador==0)
            {
                apagarLed();//apagar todos los leds
                gpio_set_level(ledROJO,     1);
                gpio_set_level(ledAMARILLO, 1);
            }
            if (contador == 5)//hasta pasados los 5 segundos no cambia de estado
            {
                contador=0;
                estadoActual = VERDE;
            }
            contador ++;
        }    
        break;
        case VERDE:
        {
            if (contador==0)
            {
                apagarLed();//apagar todos los leds
                gpio_set_level(ledVERDE,    1);
            }
            if (contador == 30)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoActual = AMARILLO;
            }
            contador ++;
        }    
        break;
        case AMARILLO:
        {
            if (contador==0)
            {
                apagarLed();//apagar todos los leds
                gpio_set_level(ledAMARILLO, 1);
            }
            if (contador == 10)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoActual = ROJO;
            }
            contador ++;
        }    
        break;
        default:
        {
            prinf("ya hiciste cagada");
            iniciarSemaforo();
        }
        break;
    }
}

//funcion que apaga todos los leds
void apagarLed()
{
    gpio_set_level(ledROJO,     0);
    gpio_set_level(ledAMARILLO, 0);
    gpio_set_level(ledVERDE,    0);
}