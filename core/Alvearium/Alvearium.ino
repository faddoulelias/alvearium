#include "includes/HiveDataPacket.hpp"
#include "includes/Environment.hpp"
#include "includes/Scale.hpp"
#include "includes/LoraConnection.hpp"

#define APP_EUI "0000000000000000"
#define APP_KEY "C8DFDC187A8281E778015F091DDE04DF"

#define LOADCELL_DOUT_PIN 7
#define LOADCELL_SCK_PIN 9

Environment *environment = nullptr;
Scale *scale = nullptr;
LoraConnection *loraConnection = nullptr;

void setup()
{
  Serial.begin(9600);
  environment = new Environment(2, 3, 4);
  scale = new Scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, 8960);
  loraConnection = new LoraConnection(APP_EUI, APP_KEY);
}

int i = 0;
void loop()
{
  Serial.println("Started loop");
  if (!loraConnection->isConnected())
  {
    Serial.println("Lora not connected");
    loraConnection->connect();
  }
  Serial.println("Lora connected");

  i++;
  std::array<float, 3> temperatures = environment->getTemperatures();
  float humidity = environment->getHumidity();
  double mass = scale->getWeight();
  HiveDataPacket packet = HiveDataPacket(temperatures, humidity, mass);

  Serial.println("Iteration " + String(i));
  Serial.println("Temperature 1 = " + String(packet.getTemperatures()[0]) + " °C");
  Serial.println("Temperature 2 = " + String(packet.getTemperatures()[1]) + " °C");
  Serial.println("Temperature 3 = " + String(packet.getTemperatures()[2]) + " °C");
  Serial.println("Humidite = " + String(packet.getHumidity()) + " %");
  Serial.println("Masse = " + String(packet.getMass()) + " kg");
  Serial.println("Packet = " + String(sizeof(packet)) + " bytes");
  Serial.println("Message = " + String(packet.showHexPacket()) + "\n");

  loraConnection->send(packet.createPacket().data);
  Serial.println("Packet = " + String(sizeof(packet)) + " bytes");
  delay(100);
}