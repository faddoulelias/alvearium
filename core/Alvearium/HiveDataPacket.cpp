#include "./includes/HiveDataPacket.hpp"

uint16_t serializeTemp(float temp)
{
    return (uint16_t)((temp + 30) * 10);
}

uint16_t serializeHumidity(int humidity)
{
    return (uint16_t)humidity;
}

uint16_t serializeMass(int mass)
{
    return (uint16_t)mass;
}

float deserializeTemp(uint16_t temp)
{
    return (float)(temp / 10.0 - 30);
}

float deserializeHumidity(uint16_t humidity)
{
    return (float)humidity;
}

double deserializeMass(uint16_t mass)
{
    return (double)mass;
}

HiveDataPacket::HiveDataPacket(std::array<float, 3> temperatures, float humidity, double mass)
{
    this->temp1 = serializeTemp(temperatures[0]);
    this->temp2 = serializeTemp(temperatures[1]);
    this->temp3 = serializeTemp(temperatures[2]);
    this->humidity = serializeHumidity(humidity);
    this->mass = serializeMass(mass);
}

std::array<float, 3> HiveDataPacket::getTemperatures()
{
    std::array<float, 3> temperatures = {
        deserializeTemp(this->temp1),
        deserializeTemp(this->temp2),
        deserializeTemp(this->temp3),
    };
    return temperatures;
}

double HiveDataPacket::getMass()
{
    return this->mass;
}

float HiveDataPacket::getHumidity()
{
    return this->humidity;
}

String HiveDataPacket::showHexPacket()
{
    LoRaDataPacket packet = this->createPacket();
    String hexPacket = "";
    String byte = "";
    for (int i = 0; i < 11; i++)
    {
        byte = String(packet.data[i], HEX);
        if (byte.length() == 1)
        {
            byte = "0" + byte;
        }
        hexPacket += byte + " ";
    }
    return hexPacket;
}

LoRaDataPacket HiveDataPacket::createPacket()
{
    LoRaDataPacket packet;
    packet.data[0] = (uint8_t)(this->temp1 >> 8) + 1;
    packet.data[1] = (uint8_t)(this->temp1) + 1;

    packet.data[2] = (uint8_t)(this->temp2 >> 8) + 1;
    packet.data[3] = (uint8_t)(this->temp2) + 1;

    packet.data[4] = (uint8_t)(this->temp3 >> 8) + 1;
    packet.data[5] = (uint8_t)(this->temp3) + 1;

    packet.data[6] = (uint8_t)(this->humidity >> 8) + 1;
    packet.data[7] = (uint8_t)(this->humidity) + 1;

    packet.data[8] = (uint8_t)(this->mass >> 8) + 1;
    packet.data[9] = (uint8_t)(this->mass) + 1;

    packet.data[10] = '\0';

    return packet;
}