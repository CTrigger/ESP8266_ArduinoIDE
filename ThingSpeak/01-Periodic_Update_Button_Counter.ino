// Libraries
#include <ESP8266WiFi.h>

// WiFi settings
const char *ssid =  "YOUR SSID";
const char *password =  "YOUR PASS";

//API
const char* host = "api.thingspeak.com";
String ApiKey = "xxxxxxxxxxxxxxxx";
String path = "/update?key=" + ApiKey; 

//Interface
int BTN_FLASH = 0;
int LED = 2;

//Data
int counter = 0;
String DATA = "";
char counterString[6];

void setup() {
  //Serial setup
  Serial.begin(9600);
  
  //interface setup
  pinMode(BTN_FLASH,INPUT);
  pinMode(LED,OUTPUT);

  //WiFi Conecting
  Serial.print("Connecting... ");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected: " + String(ssid));
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(LED, digitalRead(BTN_FLASH));
  
  if(digitalRead(BTN_FLASH) == LOW){
    //Button Event Counter
    counter++;
  }
  
  dtostrf(counter, 3, 1, counterString);
  
  DATA = "";
  DATA += "GET " + String(path) + 
  DATA += "&field1=" + String(counterString) + 
  DATA += " HTTP/1.1\r\n" +
  DATA += "Host: " + String(host) +
  DATA += "\r\n";
  DATA += "Connection: keep-alive\r\n";
  
  WiFiClient client;
  Serial.println("Requesting the API Service");
  if(!client.connect(host, 80)){
    Serial.println("Connection failed...");
    return;
  }else{
    Serial.println("Connection Granted");
  }

  Serial.println("Sending Data: \r\n" + DATA);
  client.println(DATA);
  Serial.println("Data Sent");
  delay(30 * 1000);
  delay(50);
}
