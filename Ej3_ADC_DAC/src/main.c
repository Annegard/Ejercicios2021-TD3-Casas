#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/adc.h>
#include <driver/dac.h>

void app_main() 
{
    //la alimentacion maxima que puede soportar el conversor es de 3.3 V
    adc1_config_width(ADC_WIDTH_12Bit);
    //Las atenucaciones son necesarias a mayores voltajes, revisar tabla
    //arriba de los 2.6 volt ya no es buena la medicion sin importar la atenuacion
    
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);//canal 0, medir entre 100 y 950 mV

    //habilito el canal uno
    dac_output_enable(DAC_CHANNEL_1);

    while (1)
    {
        int lectura = adc1_get_raw(ADC1_CHANNEL_0);
        printf("El valor del ADC1 es %d\n", lectura);

        dac_output_voltage(DAC_CHANNEL_1, (lectura*255/40965));

        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}