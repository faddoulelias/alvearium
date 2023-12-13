#include "./includes/TemperatureSensor.hpp"

TemperatureSensor::TemperatureSensor(uint8_t sensorPin)
{
    oneWire = new OneWire(sensorPin);
    sensors = new DallasTemperature(oneWire);
    _sensorPin = sensorPin;
    sensors->begin();
}

TemperatureSensor::~TemperatureSensor()
{
    delete oneWire;
    delete sensors;
}

float TemperatureSensor::getTemperature()
{
    sensors->requestTemperatures();
    return sensors->getTempCByIndex(0);
}
