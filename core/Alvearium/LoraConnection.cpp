#include "./includes/LoraConnection.hpp"

LoraConnection::LoraConnection(String appEui, String appKey, _lora_band band)
{
    this->_appEui = appEui;
    this->_appKey = appKey;
    this->_isConnected = false;
    this->_errorCount = 0;
    this->_modem.begin(band);
}

bool LoraConnection::connect()
{
    if (this->_isConnected)
    {
        return true;
    }

    int ret = this->_modem.joinOTAA(this->_appEui, this->_appKey);
    if (ret)
    {
        this->_isConnected = true;
        this->_modem.minPollInterval(60);
        delay(100);
        this->_errorCount = 0;
        return true;
    }
    else
    {
        this->_errorCount++;
        this->_isConnected = false;
        return false;
    }
}

bool LoraConnection::isConnected()
{
    return this->_isConnected;
}

bool LoraConnection::send(String payload)
{
    this->_modem.beginPacket();
    this->_modem.write(payload.c_str());
    int err = this->_modem.endPacket();

    return (err == 0);
}
