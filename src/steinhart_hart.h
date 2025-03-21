#ifndef STEINHART_H
#define STEINHART_H

#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "def.h"
#include "utils.h"

constexpr float STEINHART_A = 1.130003202730337e-3;
constexpr float STEINHART_B = 2.828517118811391e-4;
constexpr float STEINHART_C = 3.235422136480058e-8;

// Calculate temperature using Steinhart-Hart equation  (Farenheit)
uint16_t get_steinhart_temp(float resistance)
{
    float log_r = log(resistance);
    float temp_k = 1.0 / (STEINHART_A + (STEINHART_B * log_r) + (STEINHART_C * log_r * log_r * log_r));
    uint16_t value = (temp_k * 1.8) - 459.67;
    return value;
}

#endif