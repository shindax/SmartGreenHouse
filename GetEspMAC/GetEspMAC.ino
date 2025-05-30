#include <ESP8266WiFi.h>

// Used Wi_Fi
// #define WORK_WI_FI 1
// #define HOME_WI_FI 1
// #define GREENHOUSE_WI_FI 1
#define MY_REDME_WI_FI 1

// #define DEBUG 1

#include "d:\Projects\Arduino\SmartGreenHouse\System\wiFiSettings.h"
#include "d:\Projects\Arduino\SmartGreenHouse\System\wifiFunctions.cpp"
#include "d:\Projects\Arduino\SmartGreenHouse\System\boards.h"
#include "d:\Projects\Arduino\SmartGreenHouse\System\boards.cpp"

const char* ssid = SSID;
const char* password = PASSWORD;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
} // setup()

void loop() 
{
  static int pass = 0 ;
  static int dataAssigned = 0 ;

  if(WiFi.status() != WL_CONNECTED){
    wiFiConnect( ssid, password );
    Serial.print( "Pass without WiFi " );
    Serial.println( pass );
    dataAssigned = 0;
  }
  else{
    if( !dataAssigned ){
//        #ifdef DEBUG
            Serial.println("Connected to the WiFi network.");
            Serial.print("IP address:\t");
            Serial.println(WiFi.localIP());         // Optionally displays our IP address.

            String MAC = getBoardMAC();
            Serial.print("Data assigned with MAC: ");
            Serial.println( MAC );

            Serial.print("Module ");
            Serial.print( getBoardName( MAC ) );
            Serial.println( " online" );
//            #endif
            dataAssigned = 1;
    }
    Serial.print( "Normal pass " );
    Serial.println( pass );
  }

  pass ++;
  delay(2000);
} // loop()

