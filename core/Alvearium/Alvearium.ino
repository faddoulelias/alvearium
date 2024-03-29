#include "includes/LoraConnection.hpp"
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>
#include <math.h>

#define TPL5110_DELAY 10
#define TPL5110_DONE 7
#define DHT22_INTERIOR 4
#define DHT22_EXTERIOR 0
#define ONE_WIRE_BUS 3
#define LOADCELL_DOUT_PIN 8
#define LOADCELL_SCK_PIN 9
#define PERCENTAGE_PIN A6
#define PHOTO_PIN A3

#define APP_EUI "0000000000000000"
#define APP_KEY "C8DFDC187A8281E778015F091DDE04DF"

DHT dhtInterrior(DHT22_INTERIOR, DHT22);
DHT dhtExterior(DHT22_EXTERIOR, DHT22);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
HX711 scale = HX711();

LoraConnection *loraConnection = nullptr;

double getPercentage()
{
    const double maxV = 3.17;
    const double minV = 2.8;
    const double targetV = 3.3;
    double voltage = analogRead(PERCENTAGE_PIN) * targetV / 1024.0;
    unsigned int percentage = (voltage - minV) / (maxV - minV) * 100;
    return percentage > 100 ? 100 : percentage;
}

double getLight()
{
    const double k = 2;
    const double voltage = analogRead(PHOTO_PIN) * 5.0 / 1024.0;
    const double LDR = 10000.0 * (5.0 / voltage - 1.0);
    const double R0 = 10000.0;
    const double light = 1.0 / pow(LDR / R0, k);
    return light;
}

double getPreciseLight()
{
    double sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += getLight();
        delay(10);
    }
    return sum / 10;
}

void setupTPL5110()
{
    pinMode(TPL5110_DELAY, OUTPUT);
    pinMode(TPL5110_DONE, OUTPUT);
    digitalWrite(TPL5110_DELAY, LOW);
    digitalWrite(TPL5110_DONE, LOW);
}

void startSensors()
{
    digitalWrite(TPL5110_DELAY, HIGH);
    delay(50);
    digitalWrite(TPL5110_DELAY, LOW);
    delay(15000);
}

void sleepSensors()
{
    digitalWrite(TPL5110_DONE, HIGH);
    delay(50);
    digitalWrite(TPL5110_DONE, LOW);
}

void setupEnvironmentSensors()
{
    dhtInterrior.begin();
    dhtExterior.begin();
    sensors.begin();
}

void setupScale()
{
    Serial.begin(9600);
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(-19753.216);
    scale.set_offset(-2108285);
}

double getWeight()
{
    double output = scale.get_units();
    return output < 0 ? 0 : output;
}

void setupBattery()
{
    pinMode(PERCENTAGE_PIN, INPUT);
    pinMode(PHOTO_PIN, INPUT);
}

void setup()
{
    int readData = 0;
    Serial.begin(9600);
    loraConnection = new LoraConnection(APP_EUI, APP_KEY);
    setupTPL5110();
    setupScale();
    setupBattery();
    setupEnvironmentSensors();
    delay(1000);
}

void loop()
{
    Serial.println("Started loop");
    if (!(loraConnection->isConnected()))
    {
        Serial.println("Lora not connected");
        loraConnection->connect();
    }
    else
    {
        Serial.println("Lora connected");
    }

    startSensors();
    sensors.requestTemperatures();
    double humidityInterior = dhtInterrior.readHumidity();
    double humidityExterior = dhtExterior.readHumidity();

    double temperatureInterior = sensors.getTempCByIndex(0);
    double temperatureExterior = sensors.getTempCByIndex(1);
    double weight = getWeight();

    double percentage = getPercentage();
    double light = getPreciseLight();

    loraConnection->send(
        String(humidityInterior) + "," +
        String(humidityExterior) + "," +
        String(temperatureInterior) + "," +
        String(temperatureExterior) + "," +
        String(weight) + "," +
        String(percentage) + "," +
        String(light));

    sleepSensors();

    delay(600000);
}