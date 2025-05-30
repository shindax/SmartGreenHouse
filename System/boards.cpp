#include "boards.h"

board boards[] = {
                    { "WITTY-1",            "F4:CF:A2:6A:FE:31" },
                    { "WITTY-2",            "3C:61:05:DA:F5:1D" },
                    { "ESP-01-1",           "68-C6-3A-C8-3A-39" },
                    { "ESP-01-2",           "18:FE:34:98:DF:82" },                    
                    { "ESP-01S-3",          "94:B9:7E:17:AD:9C" },
                    { "ESP-01S-4",          "BC:FF:4D:24:40:0E" },
                    { "ESP_01_5",           "18:FE:34:98:E0:D0" },
                    { "Wemos-D1-mini-V4-1", "B4:E6:2D:2A:4E:2F" },
                    { "Wemos-D1-mini-2",    "DC:4F:22:65:E5:1F" }
                };

int boardsArraySize = sizeof( boards ) / sizeof( const char * ) / 2;

String getBoardMAC( void )
{
  return WiFi.macAddress();
}

const char * getBoardName( String MAC )
{
  for( int i = 0 ; i < boardsArraySize; i ++ )
    if( !strcmp( boards[ i ].MAC, MAC.c_str() ) )
        return boards[ i ].name;
  
  return MAC.c_str();
}
