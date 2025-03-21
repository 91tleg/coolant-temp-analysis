#include "steinhart_hart.h"

float get_steinhart_temp(float resistance)
{
    if (resistance <= 0)
        return -1;
    float log_r = log(resistance);
    float log_r3 = log_r * log_r * log_r;
    float temperature_k = 1.0 / (STEINHART_A + (STEINHART_B * log_r) + (STEINHART_C * log_r3));
    float temperature_f = (temperature_k * 1.8) - 459.67; // Convert Kelvin to Fahrenheit
    
    return temperature_f;
}