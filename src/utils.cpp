#include "utils.h"

float get_resistance(float average_analog_reading, float voltage)
{
    if (voltage <= 0 || voltage >= V_IN)
        return -1;
    return (RESISTOR_VALUE * average_analog_reading) / (ESP_ANALOG_MAX - average_analog_reading);
}

float get_voltage(float average_analog_reading)
{
    if (average_analog_reading <= 0 || average_analog_reading >= ESP_ANALOG_MAX)
        return -1;
    return (average_analog_reading / 4095.0) * V_IN;
}