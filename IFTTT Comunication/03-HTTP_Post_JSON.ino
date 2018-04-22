// Libraries
#include <ESP8266WiFi.h>

// WiFi settings
const char *ssid =  "Your SSID Here";                // Rede Wifi 
const char *password =  "Your Password Here";       // PSW rede Wifi

// IFTTT settings
const char* host = "maker.ifttt.com";
const char* eventName   = "Your Event Trigger Here";
const char* key = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

// Interface
int button = 0;
int button_Status = 0;
int counter;

void setup() {
  //Define Serial Interface Frequency
  Serial.begin(9600);
  delay(10);
  
  //Initial Value where we send in JSON
  counter = 0;
  
  //Button trigger to send the HttpPost Request
  pinMode(button,INPUT);

  // We start by connecting to a WiFi network
  Serial.println("Connecting to " + String(ssid));
  
  //Connecting
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  //Local IP share
  Serial.println("====================");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Wait Event Trigger
  button_Status = digitalRead(button);
  if (button_Status != HIGH){
    sendRequest();
    
  }
  
  //This delay is needed for TCP Protocols running in background
  delay(50);
}

void sendRequest(){
    Serial.println();
    Serial.println("=====Start=====");
    counter++;
    Serial.print("Button Event: ");
    Serial.println(counter);
    Serial.println();
    
    Serial.print("Connecting to ");
    Serial.println(host);
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
    
    // We now create a URI for the request
    String url = "/trigger/";
    url += eventName;
    url += "/with/key/";
    url += key;

    // Prepare JSON data to post
    String jsonData = "";
    jsonData = jsonData +   "{\"value1\":\"" + counter + "\",\"value2\":\"" + counter + "\",\"value3\":\"" + counter + "\"}";

    Serial.println("===================");
    Serial.println("JSON Data Attributes");
    Serial.println("===================");
    Serial.println("Size: " + String(jsonData.length()));
    Serial.println("Data: " + jsonData);
    Serial.println("===================");
    Serial.println();
    
    Serial.print("Requesting URL: ");
    Serial.println(url);
    Serial.println();

    //Build the Header for HTTP Request
    String data = "";
    data += "POST " + url + " HTTP/1.1" + "\r\n";
    data += "Host: " + String(host) + "\r\n";
    data += "Connection: close\r\n";
    data += "Content-Type: application/json\r\n";
    data += "Content-Length: " + String(jsonData.length()) + "\r\n\r\n";
    data += jsonData + "\r\n";
    
    
    Serial.println("===================");
    Serial.println("   Data Test       ");
    Serial.println("===================");
    Serial.println(data);
    Serial.println("===================");
    client.println(data);
   
    Serial.println("===================");
    Serial.println("   Sending Data    ");
    Serial.println("===================");
    int timeout = millis() + 5000;
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    
    Serial.println("===================");
    Serial.println("  Receiving Data   ");
    Serial.println("===================");
    while(client.available()){
      String line = client.readStringUntil('\r\n');
      Serial.println(line);
    }
    Serial.println("===================");
    Serial.println();
    
    Serial.println("====Finish====");
}
