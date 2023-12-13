#include "HX711.h"
#define LOADCELL_DOUT_PIN 7
#define LOADCELL_SCK_PIN 9

HX711 *scale;

void setup()
{
  Serial.begin(9600);
  scale = new HX711();
  scale->begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale->set_scale(8960);
  scale->tare();
}

void loop()
{
  double weight = (scale->get_units() / 2.2046);
  Serial.println(weight);
}
