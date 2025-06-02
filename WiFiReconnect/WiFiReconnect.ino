/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/solved-reconnect-esp8266-nodemcu-to-wifi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "shRedmiNote";
const char* password = "shindax110";

unsigned long previousMillis = 0;
unsigned long interval = 2000;

void initWiFi( void ) 
{
  static int count = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED && count ++ <= 10 ) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  //The ESP8266 tries to reconnect automatically when the connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}// void initWiFi( void )

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop( void ) 
{
  static int count = 0;
  //print the Wi-Fi status every 30 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >=interval){
    switch (WiFi.status()){
      case WL_NO_SSID_AVAIL:
        Serial.println("Configured SSID cannot be reached");
        break;
      case WL_CONNECTED:
        Serial.println("Connection successfully established");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Connection failed");
        break;
    }// switch (WiFi.status()){
    Serial.printf("Connection status: %d\n", WiFi.status());
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());

    Serial.print("count: ");
    Serial.println( count ++ );

    previousMillis = currentMillis;
  }// if (currentMillis - previousMillis >=interval){
}// void loop( void ) 