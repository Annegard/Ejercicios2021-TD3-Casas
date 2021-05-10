#include "../include/led.h"
#include "../include/global.h"

typedef enum
    {
        ROJO,
        ROJO_AMARILLO,
        VERDE,
        AMARILLO
    }estadoMEF_t;
    //variable de estado (global)
    estadoMEF_t estadoLEDActual;  

static uint8_t L1,L2,L3;
int  Sentido=0, contador=0;

void inicializarLed(int led1,int led2,int led3){
    L1=led1; L2=led2;L3=led3;

    gpio_pad_select_gpio(led1);
    gpio_set_direction(led1, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(led2);
    gpio_set_direction(led2, GPIO_MODE_DEF_OUTPUT);

    gpio_pad_select_gpio(led3);
    gpio_set_direction(led3, GPIO_MODE_DEF_OUTPUT);

}

void Secuencia(bool state){
    if (state == true){
        actualizarSemaforo();
    }
    else
    {
        actualizarIntermitente();
    }
}

void actualizarSemaforo()
{
    switch (estadoLEDActual)
    {
        case ROJO:
        {
            if (contador==0)
            {
                prenderLed(ROJO);//rojo
            }
            if (contador == 60)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = ROJO_AMARILLO;
            }
            contador ++;
        }    
        break;
        case ROJO_AMARILLO:
        {
            if (contador==0)
            {
                prenderLed(ROJO_AMARILLO);//rojo
            }
            if (contador == 5)//hasta pasados los 5 segundos no cambia de estado
            {
                contador=0;
                estadoLEDActual = VERDE;
            }
            contador ++;
        }    
        break;
        case VERDE:
        {
            if (contador==0)
            {
                prenderLed(VERDE);//rojo
            }
            if (contador == 30)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = AMARILLO;
            }
            contador ++;
        }    
        break;
        case AMARILLO:
        {
            if (contador==0)
            {
                prenderLed(AMARILLO);//rojo
            }
            if (contador == 10)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = ROJO;
            }
            contador ++;
        }    
        break;
        default:
        {
            iniciarSecuencia();
            printf("ya hiciste cagada");
        }
        break;
    }
}

void actualizarIntermitente(){
    switch (estadoLEDActual)
    {
        case ROJO:
        {
            if (contador==0)
            {
                prenderLed(ROJO);//rojo
            }
            if (contador == 1)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = VERDE;
            }
            contador ++;
        } 
        break;
        case VERDE:
        {
            if (contador==0)
            {
                prenderLed(VERDE);//rojo
            }
            if (contador == 1)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = AMARILLO;
            }
            contador ++;
        }    
        break;
        case AMARILLO:
        {
            if (contador==0)
            {
                prenderLed(AMARILLO);//rojo
            }
            if (contador == 1)//hasta pasados los 60 segundo no cambia de estado
            {
                contador=0;
                estadoLEDActual = ROJO;
            }
            contador ++;
        }    
        break;
        default:
        {
            iniciarSecuencia();
            printf("ya hiciste cagada");
        }
        break;
    }
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

void iniciarSecuencia()
{
    apagarLed();

    contador=0;
    estadoLEDActual = ROJO;
}

//funcion que apaga todos los leds
void apagarLed(){
    gpio_set_level(ledROJO,     0);
    gpio_set_level(ledAMARILLO, 0);
    gpio_set_level(ledVERDE,    0);
}
