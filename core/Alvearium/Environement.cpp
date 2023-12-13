#include "./includes/Environment.hpp"

Environment::Environment(uint8_t dhtPin, uint8_t ds18b20Pin1, uint8_t ds18b20Pin2)
{
    this->_dhtPin = dhtPin;
    this->_ds18b20Pin1 = ds18b20Pin1;
    this->_ds18b20Pin2 = ds18b20Pin2;

    humiditySensor = new HumiditySensor(DHT22, dhtPin);
    temperatureSensor1 = new TemperatureSensor(ds18b20Pin1);
    temperatureSensor2 = new TemperatureSensor(ds18b20Pin2);
}

Environment::~Environment()
{
    delete humiditySensor;
    delete temperatureSensor1;
    delete temperatureSensor2;
}

std::array<float, 3> Environment::getTemperatures()
{
    std::array<float, 3> temperatures = {
        temperatureSensor1->getTemperature(),
        temperatureSensor2->getTemperature(),
        humiditySensor->getTemperature()};

    return temperatures;
}

float Environment::getHumidity()
{
    return humiditySensor->getHumidity();
}
