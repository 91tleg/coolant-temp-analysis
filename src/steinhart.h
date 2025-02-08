#ifndef STEINHART_H
#define STEINHART_H

#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "def.h"

int16_t coolant_temp_steinhart = 0;
int16_t coolant_temp_farenheit = 0;
constexpr float STEINHART_A = 0.000957515;
constexpr float STEINHART_B = 0.0003360047695925;
constexpr float STEINHART_C = -0.000000228248698;

void calculate_steinhart_temp(float average_reading_adc)
{
    float resistance = (RESISTOR_VALUE * average_reading_adc) / (1023.0 - average_reading_adc);

    // Calculate temperature using Steinhart-Hart equation
    float log_r = log(resistance);
    float steinhart = STEINHART_A + (STEINHART_B * log_r) + (STEINHART_C * log_r * log_r * log_r);
    float temp_kelvin = 1.0 / steinhart;    // Invert
    coolant_temp_farenheit = (temp_kelvin * 1.8) - 459.67;
}

#endif