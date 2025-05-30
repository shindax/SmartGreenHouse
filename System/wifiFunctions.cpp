#include <ESP8266WiFi.h>
#include "boards.h"

//#define DEBUG 1

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


String leaveOneDigitAfterTheDecimalPoint( float val )
{
  int intVal = val;
  int fraction = val / 10;
  String newVal = String( intVal );
  newVal += ".";
  newVal += fraction;
  return newVal;
}// String leaveOneDigitAfterTheDecimalPoint( float val )