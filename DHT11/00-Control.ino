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
  String data = "";
  data += "Humidity: " + String(h) + "%\r\n";
  data += "Temperature: " + String(t) + "°C\r\n";
  Serial.println(data);
  
  delay(3 * 1000);//3 seconds wait
}
