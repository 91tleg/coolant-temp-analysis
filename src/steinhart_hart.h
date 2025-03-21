#ifndef STEINHART_HART_H
#define STEINHART_HART_H

#include <math.h>
#include "def.h"
#include "utils.h"

constexpr float STEINHART_A = 1.130003202730337e-3;
constexpr float STEINHART_B = 2.828517118811391e-4;
constexpr float STEINHART_C = 3.235422136480058e-8;

// Calculate temperature using Steinhart-Hart equation (Farenheit)
float get_steinhart_temp(float resistance);

#endif