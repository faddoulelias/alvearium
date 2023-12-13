#pragma once
#include <DallasTemperature.h>
#include <array>

struct LoRaDataPacket
{
    char data[11];
};

struct HiveDataPacket
{
private:
    uint16_t temp1;    // 2 bytes
    uint16_t temp2;    // 2 bytes
    uint16_t temp3;    // 2 bytes
    uint16_t humidity; // 2 byte
    uint16_t mass;     // 2 bytes

public:
    HiveDataPacket(std::array<float, 3> temperatures, float humidity, double mass);
    std::array<float, 3> getTemperatures();
    double getMass();
    float getHumidity();
    String showHexPacket();
    LoRaDataPacket createPacket();
};