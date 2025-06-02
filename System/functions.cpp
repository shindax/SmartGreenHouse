#include <ESP8266WiFi.h>

#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

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