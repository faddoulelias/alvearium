#pragma once
#include "DHT.h"

class HumiditySensor
{
private:
    uint8_t _sensorType;
    uint8_t _sensorPin;
    DHT *_dht = nullptr;

public:
    HumiditySensor(uint8_t sensorType, uint8_t sensorPin);
    ~HumiditySensor();
    float getTemperature();
    float getHumidity();
};