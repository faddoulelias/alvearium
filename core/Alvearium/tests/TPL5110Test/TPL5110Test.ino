#include "../../includes/LoraConnection.hpp"

#define TPL5110_DELAY 10
#define TPL5110_DONE 7
#define DHT22_INTERIOR 4
#define DHT22_EXTERIOR 0
#define ONE_WIRE_BUS 3
#define LOADCELL_DOUT_PIN 8
#define LOADCELL_SCK_PIN 9

#define APP_EUI "0000000000000000"
#define APP_KEY "C8DFDC187A8281E778015F091DDE04DF"

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>

DHT dhtInterrior(DHT22_INTERIOR, DHT22);
DHT dhtExterior(DHT22_EXTERIOR, DHT22);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
HX711 scale = HX711();

LoraConnection *loraConnection = nullptr;

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
    delay(2000);
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

void setup()
{
    int readData = 0;
    Serial.begin(9600);
    setupTPL5110();
    setupScale();
    setupEnvironmentSensors();
    delay(1000);
}

void loop()
{
    startSensors();
    sensors.requestTemperatures();
    double humidityInterior = dhtInterrior.readHumidity();
    double humidityExterior = dhtExterior.readHumidity();

    double temperatureInterior = sensors.getTempCByIndex(0);
    double temperatureExterior = sensors.getTempCByIndex(1);
    double weight = getWeight();

    Serial.print("Humidity Interrieur: ");
    Serial.println(humidityInterior);

    Serial.print("Humidity Exterieur: ");
    Serial.println(humidityExterior);

    Serial.print("Temperature Interrieur: ");
    Serial.println(temperatureInterior);
    Serial.print("Temperature Exterieur: ");
    Serial.println(temperatureExterior);

    Serial.print("Weight: ");
    Serial.println(weight);
    Serial.println();
    sleepSensors();

    delay(1000);
}