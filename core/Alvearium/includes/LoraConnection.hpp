#pragma once
#include <MKRWAN.h>

class LoraConnection
{
private:
    LoRaModem _modem;
    String _appEui;
    String _appKey;
    bool _isConnected;
    size_t _errorCount;

public:
    LoraConnection(String appEui, String appKey, _lora_band band = EU868);
    bool connect();
    bool isConnected();
    bool send(String payload);
};