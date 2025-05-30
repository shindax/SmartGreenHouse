#include <ESP8266WiFi.h>

#ifndef BOARD_H
#define BOARD_H

typedef struct _board{
  const char * name;
  const char * MAC;
} board;

extern board boards[];
extern int boardsArraySize;

const char * getBoardName( String MAC );
String getBoardMAC( void );

#endif