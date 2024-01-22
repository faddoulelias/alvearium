#define PERCENTAGE_PIN A6
#define PHOTO_PIN A3
#include <math.h>

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

void setupBattery()
{
    pinMode(PERCENTAGE_PIN, INPUT);
    pinMode(PHOTO_PIN, INPUT);
}

void setup()
{
    int readData = 0;
    Serial.begin(9600);
    setupBattery();
    delay(1000);
}

void loop()
{
    Serial.println("Started loop");

    double percentage = getPercentage();
    double light = getPreciseLight();

    Serial.print("Percentage: ");
    Serial.println(percentage);
    Serial.print("Light: ");
    Serial.println(light);
    delay(500);
}