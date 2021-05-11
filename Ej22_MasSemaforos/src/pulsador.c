/*==================[ Inclusiones ]============================================*/
#include "pulsador.h"
#include "freertos/semphr.h" //librería para el uso de semaforos

/*==================[ Definiciones ]===================================*/

#define T_REBOTE_MS   40
#define T_REBOTE pdMS_TO_TICKS(T_REBOTE_MS)
#define SALIDA_PRUEBA   GPIO_NUM_26

/*==================[Prototipos de funciones]======================*/

static void errorPulsador( void );
static void botonLiberado( void );

void tareaA( void* taskParmPtr );

/*==================[Variables]==============================*/

pulsadorInfo pulsadorA;

extern SemaphoreHandle_t semaforo;

/*==================[Implementaciones]=================================*/

void inicializarPulsador( void )
{
    pulsadorA.tecla             = GPIO_NUM_5; 
    pulsadorA.estado            = ALTO;             //Estado inicial
    semaforo = xSemaphoreCreateBinary();  //creo un solo semaforo binario

    gpio_pad_select_gpio(2);
    gpio_set_direction(2, GPIO_MODE_OUTPUT);

    if(semaforo == NULL)
    {
        printf("No se pudo crear el semaforo\n");
        while(true);
    }

    gpio_pad_select_gpio(pulsadorA.tecla);
    gpio_set_direction(pulsadorA.tecla , GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsadorA.tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna

    gpio_pad_select_gpio(SALIDA_PRUEBA);
    gpio_set_direction(SALIDA_PRUEBA, GPIO_MODE_OUTPUT);
 
    // Crear tareas en freeRTOS
    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaA,                     	// Funcion de la tarea a ejecutar
        "tareaA",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}

static void errorPulsador( void )
{
    pulsadorA.estado = ALTO;
}

void actualizarPulsador()
{
    switch( pulsadorA.estado )
    {
        case BAJO:
            if( gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = ASCENDENTE;
            }
            break;

        case ASCENDENTE:
            gpio_set_level( 2, 1 );
            printf("pulsador liberado \n");
            if( gpio_get_level( pulsadorA.tecla ) ){
                pulsadorA.estado = ALTO;
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
                gpio_set_level( 2, 0 );
                printf("pulsador apagado \n");
                pulsadorA.estado = BAJO;
                botonLiberado();
            }
            else{
                pulsadorA.estado = ALTO;
            }
            break;

        default:
            errorPulsador();
            break;
    }
}

/* accion de el evento de tecla liberada */
static void botonLiberado()
{
    xSemaphoreGive( semaforo );//liberar semaforo
}

void tareaA( void* taskParmPtr )
{
    while( true )
    {
        actualizarPulsador();
        vTaskDelay( T_REBOTE_MS );
    }
}