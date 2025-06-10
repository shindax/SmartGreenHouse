/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/solved-reconnect-esp8266-nodemcu-to-wifi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define WORK_WI_FI
// #define MY_REDME_WI_FI 1
// #define GREENHOUSE_WI_FI

#include "systemSettings.h"

#define DEBUG 1

#define RED_LED   15
#define GREEN_LED 12
#define BLUE_LED  13

#define RED_LED_ON digitalWrite(RED_LED, HIGH);
#define RED_LED_OFF digitalWrite(RED_LED, LOW);

#define GREEN_LED_ON digitalWrite(GREEN_LED, HIGH);
#define GREEN_LED_OFF digitalWrite(GREEN_LED, LOW);

#define BLUE_LED_ON digitalWrite(BLUE_LED, HIGH);
#define BLUE_LED_OFF digitalWrite(BLUE_LED, LOW);

#define ALL_LEDS_OFF digitalWrite(GREEN_LED, LOW); digitalWrite(RED_LED, LOW); digitalWrite(BLUE_LED, LOW);

unsigned long previousMillis = 0;
unsigned long interval = 2000;
ESP8266WebServer server(80); //Server on port 80

String RSSI = "";
int count = 0;

void handleRoot( void ) 
{
#ifdef DEBUG
 Serial.println("You called root page");
#endif 
 String s = "<style>h1{font-size:100pt;margin-bottom:10px}span{font-size:80pt;}</style>";

 s += "<script>";
 s += "setInterval(function(){let count = parseInt(document.getElementById('count').textContent); count ++; document.getElementById('count').textContent = count; }, 1000);";
 s += "setInterval(function(){ document.getElementById('rssi').innerHTML = '";
 s += "'; }, 1000);";
 s += "</script>";
 
 s += "<center><h1 id='rssi'></h1>";
 s += "<span>pass: </span>";
 s += "<span id='count'>1</span><br>";
 s += "<hr></center>";
 server.send(200, "text/html", s); //Send web page
}

  // Serial.print("WL_IDLE_STATUS      = 0\n"
  //              "WL_NO_SSID_AVAIL    = 1\n"
  //              "WL_SCAN_COMPLETED   = 2\n"
  //              "WL_CONNECTED        = 3\n"
  //              "WL_CONNECT_FAILED   = 4\n"
  //              "WL_CONNECTION_LOST  = 5\n"
  //              "WL_WRONG_PASSWORD   = 6\n"
  //              "WL_DISCONNECTED     = 7\n");

void setup() 
{
  pinMode( RED_LED, OUTPUT );
  pinMode( GREEN_LED, OUTPUT );
  pinMode( BLUE_LED, OUTPUT );  
  ALL_LEDS_OFF;

  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  
  server.on("/", handleRoot);
  server.begin();
}

void loop( void ) 
{
  int rssi;

  //print the Wi-Fi status every 30 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >=interval){
    switch (WiFi.status()){
      case WL_NO_SSID_AVAIL:
        Serial.println("Configured SSID cannot be reached");
        ALL_LEDS_OFF;
        RED_LED_ON;
        break;
      case WL_CONNECTED:
      rssi = 100 + WiFi.RSSI();
      RSSI = String("RSSI: ") + String( rssi ) + String("dB");
#ifdef DEBUG
        Serial.print("Connection successfully established with IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("Hostname: ");
        Serial.println(WiFi.hostname());
#endif        
        ALL_LEDS_OFF;
        GREEN_LED_ON;
        break;
      case WL_DISCONNECTED:
        Serial.println("Connection failed");
        ALL_LEDS_OFF;        
        BLUE_LED_ON;
        break;
    }// switch (WiFi.status()){

#ifdef DEBUG
    Serial.printf("Connection status: %d\n", WiFi.status());
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());

    Serial.print("count: ");
    Serial.println( count );
#endif
    previousMillis = currentMillis;
    count ++;
  }// if (currentMillis - previousMillis >=interval){
  server.handleClient();
}// void loop( void ) 
