#pragma once
#include "HX711.h"

class Scale
{
private:
    HX711 *scale;
    float calibration_factor;
    uint8_t dout_pin;
    uint8_t sck_pin;

public:
    Scale(uint8_t dout_pin, uint8_t sck_pin, float calibration_factor);
    double getWeight();
};