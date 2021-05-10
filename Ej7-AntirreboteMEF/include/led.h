#ifndef led_H_
#define led_H_

    #include "../include/global.h"

    void inicializarLed(int Led1, int Led2, int Led3);
    void Secuencia(bool state);
    void actualizarIntermitente();
    void prenderLed(int num);
    void iniciarSecuencia();
    void apagarLed();
    void actualizarSemaforo();
#endif