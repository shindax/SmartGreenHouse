#include <ESP8266WiFi.h>
#include "boards.h"

//#define DEBUG 1

#ifndef WIFI_FUNCTIONS_CPP
#define WIFI_FUNCTIONS_CPP

void wiFiConnect( const char* ssid, const char* password )
{
  int pass = 0;
  delay(1000);
  WiFi.begin(ssid, password);               // Initialize WiFi on the ESP8266

  while ( WiFi.status() != WL_CONNECTED && pass ++ < 10 ) {
    delay(500);
    #ifdef DEBUG
      Serial.print("Connecting to WiFi. Attempt ");
      Serial.println( pass );
    #endif
  }
}// void wiFiConnect( void )


void initWiFi( void ) 
{
  static int count = 0;
  WiFi.mode(WIFI_STA);
  WiFi.hostname(getBoardHostName(getBoardMAC()));

  WiFi.begin(SSID, PASSWORD);
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

String leaveOneDigitAfterTheDecimalPoint( float val )
{
  int intVal = val;
  int fraction = val / 10;
  String newVal = String( intVal );
  newVal += ".";
  newVal += fraction;
  return newVal;
}// String leaveOneDigitAfterTheDecimalPoint( float val )


#endif
