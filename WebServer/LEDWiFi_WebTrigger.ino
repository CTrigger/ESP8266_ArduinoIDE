//Libraries
#include <ESP8266WiFi.h>

//definir rede
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASS";

//WebServices Setup
int portServices = 80;
WiFiServer server(portServices);

//Interface
int ledWifi = 2;
int btnFlash = 0;

void setup() {
  //Serial Setup
  Serial.begin(9600);

  //Interface Setup
  pinMode(ledWifi, OUTPUT);
  pinMode(btnFlash,INPUT);
 
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println("Connecting to " + String(ssid));
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  Serial.println(":" + String(portServices));
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("Waiting Clients");
  while(!client.available()){
    delay(1);
  }
  Serial.println("\r\nClient Availble");
  
  String req = client.readStringUntil('\r');
  Serial.println("Message from Requester");
  Serial.println(req);
  Serial.println("Message END");
  client.flush();
 
  String Page = "";
 
  Page += "HTTP/1.1 200 OK\r\n";
  Page += "Content-Type: text/html\r\n\r\n";
  
  Page += "<!DOCTYPE HTML>\r\n";
  Page += "<html lang='en'>";
  Page += "<head>";
  Page +=   "<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>";
  Page +=   "<title>ESP8266 Web Server</title>";
  Page +=   "<link rel='icon' href='https://cdn.metroui.org.ua/favicon.ico' type='image/x-icon'>";
  Page +=   "<link rel='stylesheet' href='https://cdn.metroui.org.ua/v4/css/metro-all.min.css'>";
  Page +=   "<link rel='stylesheet' href='https://cdn.metroui.org.ua/v4/css/schemes/darcula.css'>";
  Page += "</head>";
  Page += "<body>";
  Page +=   "<div class='container'>";
  Page +=     "<h1>ESP8266 Web Server</h1>";
  Page +=     "<h4>CTrigger Example</h4>";
  Page +=     "<p><a href='http://github.com/CTrigger' target='_blank'>Visit Me</a></p>";
  Page +=     "<p><a href='https://metroui.org.ua' target='_blank'>CSS Source</a></p>";
  Page +=     "<p>";
  Page +=       "LED - "; 
  Page +=       "<a href=\"?led=on\" class='button bg-green'>ON</a>";
  Page +=       "<a href=\"?led=off\" class='button bg-red'>OFF</a>";
  Page +=     "</p>";
  Page +=   "</div>";
  Page += "</body>";
  Page += "</html>\r\n";
 
  client.println(Page);
  client.flush();
 
  if (req.indexOf("on") != -1){
    digitalWrite(ledWifi, LOW);
    Serial.println("Led On");
  }
  else if (req.indexOf("off") != -1){
    digitalWrite(ledWifi, HIGH);
    Serial.println("Led Off");
  }
  else {
    Serial.println("Action END");
  }
  Serial.println("Client Disonnected");
  Serial.println("==============================\r\n");
}
