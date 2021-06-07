#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_22
#define SALIDA2     GPIO_NUM_23
#define PROCESADORA 0
#define PROCESADORB 1
#define PERIODO_MS                    2000
#define PERIODO          pdMS_TO_TICKS(PERIODO_MS)

void tareaDestelloB( void* taskParmPtr ); //Prototipo de la función de la tarea
void tareaDestelloC( void* taskParmPtr ); //Prototipo de la función de la tarea
extern portMUX_TYPE mux;
extern u_int16_t contador;

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsadores();

     BaseType_t tarea_B = xTaskCreatePinnedToCore(
    	tareaDestelloB,                     	// Funcion de la tarea a ejecutar
        "tareaDestelloB",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    // Gestion de errores
	if(tarea_B == pdFAIL)
	{
		//printf( "Error al crear la tarea B.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}

    BaseType_t tarea_C = xTaskCreatePinnedToCore(
    	tareaDestelloC,                     	// Funcion de la tarea a ejecutar
        "tareaDestelloC",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    // Gestion de errores
	if(tarea_C == pdFAIL)
	{
		//printf( "Error al crear la tarea C.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}

// Implementacion de funcion de la tarea B
void tareaDestelloB( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        portENTER_CRITICAL(&mux);

        uint16_t auxiliar = (contador / 2);
        portEXIT_CRITICAL(&mux);

        gpio_set_level( SALIDA1, 1 );
        vTaskDelay( pdMS_TO_TICKS(auxiliar) );
        gpio_set_level( SALIDA1, 0 );
        vTaskDelay(pdMS_TO_TICKS(auxiliar) );

        
    }
}

// Implementacion de funcion de la tarea C
void tareaDestelloC( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    TickType_t xPeriodicity = PERIODO;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // ---------- Bucle infinito --------------------------
    while( true )
    {
        portENTER_CRITICAL(&mux);

        uint16_t auxiliar2 = (2 * contador);

         if (contador > 100)
        {
            contador= contador - 100;    
        } 
        portEXIT_CRITICAL(&mux);
        

        gpio_set_level( SALIDA2, 1 );
        vTaskDelay(pdMS_TO_TICKS(auxiliar2));
        gpio_set_level( SALIDA2, 0 );
        
        vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
    }
}