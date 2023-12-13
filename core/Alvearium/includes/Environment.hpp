#pragma once
#include "HumiditySensor.hpp"
#include "TemperatureSensor.hpp"
#include <array>

class Environment
{
private:
    HumiditySensor *humiditySensor = nullptr;
    TemperatureSensor *temperatureSensor1 = nullptr;
    TemperatureSensor *temperatureSensor2 = nullptr;

    uint8_t _dhtPin;
    uint8_t _ds18b20Pin1;
    uint8_t _ds18b20Pin2;

public:
    Environment(uint8_t dhtPin, uint8_t ds18b20Pin1, uint8_t ds18b20Pin2);
    ~Environment();

    std::array<float, 3> getTemperatures();
    float getHumidity();
};