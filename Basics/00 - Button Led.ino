//Libraries
#include<ESP8266WiFi.h>

// Variables
int Button = 0;
int Led = 2;

void setup(){
  //for debug  issues
  Serial.begin(9600);
  
  //pin Setups
  pinMode(Led,OUTPUT);
  pinMode(Button,INPUT);
}

void loop(){
  //make button Flash in esp8266 control the led in board ON/OFF
  digitalWrite(Led,digitalRead(Button));
}
