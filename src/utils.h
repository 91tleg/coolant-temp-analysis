#ifndef UTILS_H
#define UTILS_H

#include "def.h"


float get_resistance(float avg_reading_adc)
{
  return (RESISTOR_VALUE * avg_reading_adc) / (1023.0 - avg_reading_adc);
}

float claculate_voltage(float avg_reading_adc)
{
    return (avg_reading_adc * V_REF) / 1023.0;
}

#endif