#ifndef STEINHART_H
#define STEINHART_H

#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "def.h"

int16_t coolant_temp_steinhart = 0;

constexpr float STEINHART_A = 0.000957515;
constexpr float STEINHART_B = 0.0003360047695925;
constexpr float STEINHART_C = -0.000000228248698;

void read_coolant_steinhart(float average_reading_adc)
{
    // Convert average reading to resistance in ohms

    float resistance = (RESISTOR * average_reading_adc) / (1023.0 - average_reading_adc);

    // Calculate temperatures using Steinhart-Hart equation
    float logR = log(resistance);
    float steinhart = STEINHART_A + (STEINHART_B * logR) + (STEINHART_C * logR * logR * logR);
    float temp_kelvin = 1.0 / steinhart;                   // Invert to get temperature in Kelvin
    int16_t temp_farenheit = temp_kelvin * 1.8 - 459.67;
}

#endif