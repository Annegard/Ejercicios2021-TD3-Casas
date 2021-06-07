#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"
#include "freertos/semphr.h" //librería para el uso de semaforos

#define VERDE     GPIO_NUM_19
#define ROJO      GPIO_NUM_21
#define RETARDO     pdMS_TO_TICKS(500)

void tareaB( void* taskParmPtr ); //Prototipo de la función de la tarea

void LED_secuencia(bool ESTADO);

SemaphoreHandle_t semaforo = NULL;

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsador();

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaB,                     	// Funcion de la tarea a ejecutar
        "tareaB",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORB
    );
    // Gestion de errores
	if(res == pdFAIL)
	{
	    printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}

// Implementacion de funcion de la tarea
void tareaB( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(VERDE);
    gpio_set_direction(VERDE, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(ROJO);
    gpio_set_direction(ROJO, GPIO_MODE_OUTPUT);

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        if(xSemaphoreTake(semaforo, RETARDO)==pdTRUE){
            LED_secuencia(true);
        }
        else{
            LED_secuencia(false);
        }
    }
}

void LED_secuencia(bool ESTADO){

    if(ESTADO)
    {
        gpio_set_level( ROJO, 1 );
        vTaskDelay( RETARDO );
        gpio_set_level( ROJO, 0 );
        vTaskDelay( RETARDO );
    }
    else{
        gpio_set_level( VERDE, 1 );
        vTaskDelay( RETARDO );
        gpio_set_level( VERDE, 0 );
        vTaskDelay( RETARDO );
    }
}