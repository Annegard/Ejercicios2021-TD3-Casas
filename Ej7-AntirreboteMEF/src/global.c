#include "../include/global.h"

unsigned long millis()
{
    return (unsigned long) (esp_timer_get_time() / 1000ULL);
}