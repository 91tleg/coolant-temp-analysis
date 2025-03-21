#include "lookup_table.h"

uint8_t adc_to_arr_index(float voltage)
{
    uint8_t arr_index = static_cast<uint8_t>((voltage / V_IN) * UINT8_MAX);
    return arr_index;
}

int16_t get_lookup_temp(uint8_t arr_index)
{
    int16_t temperature = static_cast<int16_t>(lookup_table[arr_index]);  
    if (temperature < 14)
    {   
        temperature += 255;
    }
    else if (temperature > (255 - 29))
    {
        temperature = -temperature;
    }
    return temperature;
}