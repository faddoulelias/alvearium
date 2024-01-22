#include "HX711.h"
#define LOADCELL_DOUT_PIN 8
#define LOADCELL_SCK_PIN 9

HX711 scale = HX711();

void setup()
{
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-19753.216);
  scale.set_offset(-2108285);
}

void loop()
{
  double weight = scale.get_units();
  Serial.println(weight);
}
