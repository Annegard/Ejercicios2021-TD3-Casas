#include "../include/Semaforo.h"

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

void iniciarSemaforo()
{
    setLed();

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
                prenderLed(ROJO);//rojo
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
                prenderLed(ROJO_AMARILLO);//rojo
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
                prenderLed(VERDE);//rojo
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
                prenderLed(AMARILLO);//rojo
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
            printf("ya hiciste cagada");
            iniciarSemaforo();
        }
        break;
    }
}

