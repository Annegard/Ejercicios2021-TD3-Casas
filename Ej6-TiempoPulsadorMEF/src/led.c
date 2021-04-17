#include "../include/led.h"
#include "../include/global.h"

static uint8_t LED1, LED2,LED3, contador=1;

void inicializarLed(gpio_int_type_t Led1,gpio_int_type_t Led2,gpio_int_type_t Led3){
    
    LED1=Led2;
    LED2=Led2;
    LED3=Led2;

    gpio_pad_select_gpio(LED1);
    gpio_set_direction(LED1, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(LED2);
    gpio_set_direction(LED2, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(LED3);
    gpio_set_direction(LED3, GPIO_MODE_DEF_OUTPUT);

    Secuencia(1);
}

void Secuencia(gpio_int_type_t pulsador)
{
    static int Sentido=0;

    if (pulsador == BOTON_A || Sentido == BOTON_A)
    {
        Sentido = pulsador;
        contador--;
    }
    else//DERECHA
    {
        Sentido==BOTON_B;
        contador++;
    }
    
    switch (contador)
    {
    case 1:
        gpio_set_level(LED1,1);
        gpio_set_level(LED2,0);
        gpio_set_level(LED3,0);
        if (Sentido==BOTON_A){//seteo del contador
            contador=3;
        }
        break;
    case 2:
        gpio_set_level(LED1,0);
        gpio_set_level(LED2,1);
        gpio_set_level(LED3,0);
        break;
    case 3:
        gpio_set_level(LED1,0);
        gpio_set_level(LED2,0);
        gpio_set_level(LED3,1);
        if (Sentido==BOTON_B){//seteo del contador
            contador=3;
        }
        break;
    default:
        ledOFF();
        break;
    }
}

void ledOFF(){
    gpio_set_level(LED1,0);
    gpio_set_level(LED2,0);
    gpio_set_level(LED3,0);
}