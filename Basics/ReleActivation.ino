//Libraries
#include<ESP8266WiFi.h>

// Variables
int Button = 0;
int Led = 2;
int Rele = 5; //D1 board

void setup(){
  //pin Setups
  pinMode(Led,OUTPUT);
  pinMode(Button,INPUT);
  pinMode(Rele,OUTPUT);
}

void loop(){
  //make button Flash in esp8266 control the led in board ON/OFF
  digitalWrite(Led,digitalRead(Button));
  digitalWrite(Rele,digitalRead(Button));
}
