#include "DHT.h"
#define DHTType DHT11
int DHTPIN = 5; //d1 pin

DHT dht(DHTPIN,DHTType,15);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print("°C  \n");
  delay(3 * 1000);
}
