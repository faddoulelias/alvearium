#include "./includes/Scale.hpp"

Scale::Scale(uint8_t dout_pin, uint8_t sck_pin, float calibration_factor)
{
    this->dout_pin = dout_pin;
    this->sck_pin = sck_pin;
    this->calibration_factor = calibration_factor;
    scale = new HX711();
    scale->begin(dout_pin, sck_pin);
    scale->set_scale(calibration_factor);
    scale->tare();
}

double Scale::getWeight()
{
    return (scale->get_units() / 2.2046);
}