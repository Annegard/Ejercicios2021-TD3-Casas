#ifndef pulsador_H_
#define pulsador_H_

    typedef enum
    {
        ALTO,
        BAJO,
        DESCENDENTE,
        ASCENDENTE    
    }estadoPulsador_t;

    //variable de estado (global)
    estadoPulsador_t estadoPulsadorActual;
    
    void iniciarPulsador(int pulsador);
    void actualizarEstadoPulsador(int pulsador);

#endif 