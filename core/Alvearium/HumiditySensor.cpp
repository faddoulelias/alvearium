#include "includes/HumiditySensor.hpp"

HumiditySensor::HumiditySensor(uint8_t sensorType, uint8_t sensorPin)
{
    _sensorType = sensorType;
    _sensorPin = sensorPin;
    _dht = new DHT(_sensorPin, _sensorType);
    _dht->begin();
}

HumiditySensor::~HumiditySensor()
{
    delete _dht;
}

float HumiditySensor::getTemperature()
{
    return this->_dht->readTemperature();
}

float HumiditySensor::getHumidity()
{
    return this->_dht->readHumidity();
}