#include <ESP8266WiFi.h>                      // Подключаем библиотеку ESP8266WiFi

#define WORK_WI_FI
// #define MY_REDME_WI_FI 1
// #define GREENHOUSE_WI_FI
// #define HOME_WI_FI
#include "systemSettings.h"

#define RELAY 0                               // Пин к которому подключен датчик
WiFiServer server(80);                        // Указываем порт Web-сервера
 
void setup( void )
{
  delay(2200);      
  Serial.begin(115200);                       // Скорость передачи 115200 
  pinMode(RELAY,OUTPUT);                      // Указываем вывод RELAY как выход
  digitalWrite(RELAY, LOW);                   // Устанавливаем RELAY в LOW (0В)
  Serial.println();                           // Печать пустой строки 
  Serial.print("Connecting to ");             // Печать "Подключение к:"
  Serial.println(SSID);                       // Печать "Название Вашей WiFi сети"
 
  WiFi.begin(SSID, PASSWORD);                 // Подключение к WiFi Сети
 
  while (WiFi.status() != WL_CONNECTED)       // Проверка подключения к WiFi сети
  { 
    delay(500);                               // Пауза 500 мкс
    Serial.print(".");                        // Печать "."
  }
  Serial.println("");                         // Печать пустой строки  
  Serial.println("WiFi connected");           // Печать "WiFi connected"
 
  server.begin();                             // Запуск сервера
  Serial.println("Server started");           // Печать "Server starte"
  Serial.print("Use this URL to connect: ");  // Печать "Use this URL to connect:" 
  Serial.print(WiFi.localIP());               // Печать выданого IP адресса          

}// void setup( void )
 
void loop( void )
{
   WiFiClient client = server.available();    // Получаем данные, посылаемые клиентом 
  if (!client)                                
  {
    return;
  }
  Serial.println("new client");               // Отправка "new client"
  while(!client.available()){                  // Пока есть соединение с клиентом 
      delay(1);                                 // пауза 1 мс
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  int value = LOW;
  if (request.indexOf("/RELAY=ON") != -1)  
  {
    Serial.println("RELAY=ON");
    digitalWrite(RELAY,LOW);
    value = LOW;
  }
  if (request.indexOf("/RELAY=OFF") != -1)  
  {
    Serial.println("RELAY=OFF");
    digitalWrite(RELAY,HIGH);
    value = HIGH;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 RELAY Control</title></head>");
  client.print("Relay is now: ");
 
  if(value == HIGH) 
  {
    client.print("OFF");
  } 
  else 
  {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("Turn <a href=\"/RELAY=OFF\">OFF</a> RELAY<br>");
  client.println("Turn <a href=\"/RELAY=ON\">ON</a> RELAY<br>");
    client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}// void loop( void )