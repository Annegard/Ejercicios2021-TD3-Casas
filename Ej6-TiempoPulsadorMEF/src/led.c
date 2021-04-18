#include "../include/led.h"
#include "../include/global.h"

static uint8_t L1,L2,L3;
int  Sentido=0;

void inicializarLed(int led1,int led2,int led3){
    L1=led1; L2=led2;L3=led3;

    gpio_pad_select_gpio(led1);
    gpio_set_direction(led1, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(led2);
    gpio_set_direction(led2, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(led3);
    gpio_set_direction(led3, GPIO_MODE_DEF_OUTPUT);

    Secuencia(1);
}

void Secuencia(int pulsador)
{
    static uint8_t contador=1;

    if (pulsador == BOTON_A || Sentido == BOTON_A)
    {
        Sentido = pulsador;
        contador--;
    }
    else{//DERECHA
        Sentido = BOTON_B;
        contador++;
    }

    switch (contador)
    {
    case 1:
        gpio_set_level(L1,1);
        gpio_set_level(L2,0);
        gpio_set_level(L3,0);
        if (Sentido==BOTON_A){//seteo del contador
            contador=3;
        }
        break;
    case 2:
        gpio_set_level(L1,0);
        gpio_set_level(L2,1);
        gpio_set_level(L3,0);
        break;
    case 3:
        gpio_set_level(L1,0);
        gpio_set_level(L2,0);
        gpio_set_level(L3,1);
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