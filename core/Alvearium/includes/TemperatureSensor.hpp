#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor
{
    OneWire *oneWire;
    DallasTemperature *sensors;
    uint8_t _sensorPin;

public:
    TemperatureSensor(uint8_t sensorPin);
    ~TemperatureSensor();
    float getTemperature();
};