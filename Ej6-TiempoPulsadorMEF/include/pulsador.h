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
    
    void iniciarPulsador(gpio_int_type_t pulsador);
    void actualizarEstadoPulsador(gpio_int_type_t pulsador);

#endif 