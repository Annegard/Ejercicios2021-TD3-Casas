/*==================[ Inclusiones ]============================================*/
#include "pulsador.h"

/*==================[ Definiciones ]===================================*/

#define T_REBOTE_MS     40
#define T_REBOTE        pdMS_TO_TICKS(T_REBOTE_MS)

/*==================[Prototipos de funciones]======================*/

static void errorPulsador( uint8_t  indice );
static void botonPresionado( uint8_t  indice );
static void botonLiberado( uint8_t  indice );

void tareaPulsador( void* taskParmPtr );

/*==================[Variables]==============================*/
gpio_int_type_t pulsadorPines[N_PULSADOR] = { GPIO_NUM_18 };

pulsadorInfo pulsadorA;
SEND_DATA    DatosAEnviar;

/*==================[Implementaciones]=================================*/
TickType_t obtenerDiferencia(uint8_t  indice)
{
    TickType_t tiempo;
    tiempo = DatosAEnviar.diferenciaTiempo;
    return tiempo;
}

void borrarDiferencia( uint8_t  indice )
{
    DatosAEnviar.diferenciaTiempo = TIEMPO_NO_VALIDO;
}

void inicializarPulsador( void )
{
    pulsadorA.tecla             = pulsadorPines[0];
    pulsadorA.estado            = ALTO;                     //Estado inicial
    pulsadorA.tiempoBajo        = TIEMPO_NO_VALIDO;
    pulsadorA.tiempoAlto        = TIEMPO_NO_VALIDO;

    DatosAEnviar.diferenciaTiempo  = TIEMPO_NO_VALIDO;
    DatosAEnviar.LED_indice = 0;

    cola = xQueueCreate( 1 , sizeof(SEND_DATA*) ); // Creación de la cola

    gpio_pad_select_gpio(pulsadorA.tecla);
    gpio_set_direction(pulsadorA.tecla , GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsadorA.tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna
 
    // Crear tareas en freeRTOS
    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaPulsador,                     	// Funcion de la tarea a ejecutar
        "tareaPulsador",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        1
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}

static void errorPulsador( uint8_t  indice )
{
    pulsadorA.estado = ALTO;
}

// pulsador_ Update State Function
void actualizarPulsador( uint8_t  indice)
{
    switch( pulsadorA.estado )
    {
        case BAJO:
            if( gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = ASCENDENTE;
            }
            break;

        case ASCENDENTE:
            if( gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = ALTO;
                botonPresionado(indice);
            }
            else{
                pulsadorA.estado = BAJO;
            }
            break;

        case ALTO:
            if( !gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = DESCENDENTE;
            }
            break;

        case DESCENDENTE:
            if( !gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = BAJO;
                botonLiberado(indice);
            }
            else{
                pulsadorA.estado = ALTO;
            }
            break;

        default:
            errorPulsador(indice);
            break;
    }
}

/* accion de el evento de tecla pulsada */
static void botonPresionado( uint8_t  indice)
{
    TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    pulsadorA.tiempoBajo = conteoTicksActuales;             //guardamos ese tiempo como referencia
}

SEND_DATA* punteroEstado = &DatosAEnviar;

/* accion de el evento de tecla liberada */
static void botonLiberado( uint8_t  indice)
{
    TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    pulsadorA.tiempoAlto    = conteoTicksActuales;
    DatosAEnviar.diferenciaTiempo  = pulsadorA.tiempoAlto - pulsadorA.tiempoBajo; //Da el tiempo que el pulsador estuvo en estado alto

    xQueueSend( cola , &punteroEstado,  portMAX_DELAY  ); // Envío dato a la la cola
}

void tareaPulsador( void* taskParmPtr )
{
    while( true )
    {
        for (int i = 0; i < N_PULSADOR; i++)
        {
            actualizarPulsador(i);
        }
        vTaskDelay( T_REBOTE );
    }
}