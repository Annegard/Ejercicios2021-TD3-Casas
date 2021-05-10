#include "../include/pulsador.h"
#include "../include/led.h"

typedef enum
    {
        ALTO,
        BAJO,
        DESCENDENTE,
        ASCENDENTE    
    }estadoPulsador_t;
    //variable de estado (global)
    estadoPulsador_t estadoPulsadorActual;  

bool ESTADO= true;

void iniciarPulsador(int pulsador){

    gpio_pad_select_gpio(pulsador);
    gpio_set_direction(pulsador, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador,GPIO_PULLDOWN_ONLY);
}

void actualizarEstadoPulsador(int pulsador){
    static unsigned long Tiempo=0;

    Secuencia(ESTADO);

    switch (estadoPulsadorActual)
    {
    case BAJO:
        if(gpio_get_level(pulsador)){
            estadoPulsadorActual = ASCENDENTE;
        }
        break;
    case ASCENDENTE:
        if (millis() > Tiempo + retardo){
            if(gpio_get_level(pulsador)){
                ESTADO = !ESTADO;
                estadoPulsadorActual = ALTO;
            }
            else{
                estadoPulsadorActual=BAJO;
            }
            Tiempo = millis();
        }
        break;
    case ALTO:
        if(!gpio_get_level(pulsador)){
            estadoPulsadorActual = DESCENDENTE;
        }
        break;
    case DESCENDENTE:
        if (millis() > Tiempo + retardo){
            if(gpio_get_level(pulsador)){
            estadoPulsadorActual = BAJO;
            }
            else{
                estadoPulsadorActual=ALTO;
            }
            Tiempo = millis();
        }
        break;
    default:
        apagarLed();
        break;
    }
}

