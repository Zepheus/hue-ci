#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <stdint.h>

// Your Wifi info
#define WIFI_SSID "XXX"
#define WIFI_PASSWORD "XXX"

// Firebase stuff
#define FIREBASE_HOST "XXX.firebaseio.com"
#define FIREBASE_PATH "/build-status/dotnet-test"

// Hue information
#define HUB_IP "192.168.1.7"
#define USER_ID "XXX"
#define LIGHT_ID 1

void setLight(bool on, uint16_t h, uint8_t s, uint8_t l);

void setup() {
  Serial.begin(9600);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to wifi: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST);
  Firebase.stream(FIREBASE_PATH);  
  Serial.println("Connected to FireBase");
  delay(500);
  setLight(true, 225, 255, 128); // blue HSL by default
}

void setLight(bool on, uint16_t h, uint8_t s, uint8_t l) {
  // hue: 0-360, s: 0-255, l: 0-255
  String payload = "{\"on\":" + (on ? String("true") : String("false")) +
  ", \"sat\":" + String(s) +
  ", \"bri\":" + String(l) + 
  ", \"hue\": " + String(h * (UINT16_MAX / 360)) + 
  ", \"effect\": \"none\" }";
  
  WiFiClient client;

  if (!client.connect(HUB_IP, 80)) {
    Serial.println("Connection to Hue Hub failed");
    return;
  }
  
  // This will send the request to the server
  client.println("PUT /api/" + String(USER_ID) + "/lights/" + String(LIGHT_ID) + "/state");
  client.println("Host: " + String(HUB_IP));
  client.println("User-Agent: ESP8266/1.0");
  client.println("Connection: close");
  client.println("Content-type: text/xml; charset=\"utf-8\"");
  client.print("Content-Length: ");
  client.println(payload.length());
  client.println();
  client.println(payload);
  
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.connected() && client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Closing connection");
}


void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     eventType.toLowerCase();
     if (eventType == "put") {
      String path = event.getString("path");
      bool success;
      if(path == "/"){
        success = event.getBool("data/success");
      } else if(path == "/success"){
        success = event.getBool("data");
      } else {
        return;
      }
      Serial.print("Path: ");
      Serial.println(path);
      Serial.print("Success: ");
      Serial.println(success);
      if(success){
        setLight(true, 107, 255, 128);
      } else {
        setLight(true, 360, 255, 128);
      }
     }
  }
}
