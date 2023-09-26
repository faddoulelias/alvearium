#include <MKRWAN.h>
#include "DHT.h"

// Code : 033
// Join EUI :   1111111111111111
// Device EUI : a8610a3439236408
// App Key : F04E52D3ADE9645BB3E12D617C896FF0

// LoRaWAN Settings
LoRaModem modem;
String appEui = "1111111111111111";
String appKey = "F04E52D3ADE9645BB3E12D617C896FF0";
bool connected;
int err_count;
short con;

// Sensors settings
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    dht.begin();
    Serial.println("Welcome to MKR WAN 1300/1310 ");
    modem.begin(EU868);
    delay(1000); // apparently the murata dislike if this tempo is removed...
    connected = false;
    err_count = 0;
    con = 0;
}

void loop()
{
    short temp = dht.readTemperature() * 100;
    short humi = dht.readHumidity() * 100;

    char msg[2] = {3, 4};
    short test = 30;
    if (!connected)
    {
        Serial.print("Join test : ");
        Serial.println(++con);
        int ret = modem.joinOTAA(appEui, appKey);
        if (ret)
        {
            connected = true;
            modem.minPollInterval(60);
            Serial.println("Connected");
            modem.dataRate(5); // switch to SF7
            delay(100);        // because ... more stable
            err_count = 0;
        }
    }
    if (connected)
    {
        int err = 0;
        modem.beginPacket();
        modem.write(temp);
        modem.write(humi);
        Serial.println((float)humi / 100.0);
        Serial.println((float)temp / 100.0);

        err = modem.endPacket();
        if (err <= 0)
        {
            Serial.print("Error : ");
            Serial.println(err);
            // Confirmation not received - jam or coverage fault
            err_count++;
            if (err_count > 50)
            {
                connected = false;
            }
            // wait for 2min for duty cycle with SF12 - 1.5s frame
            for (int i = 0; i < 120; i++)
            {
                delay(1000);
            }
        }
        else
        {
            err_count = 0;
            // wait for 20s for duty cycle with SF7 - 55ms frame
            delay(20000);
            Serial.println("Message envoyé");
        }
    }
}