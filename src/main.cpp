#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "DHT.h"
#include <Hash.h>
#include  "miserver.h"

//Se inicializa web socket en el puerto 81
WebSocketsServer webSocket = WebSocketsServer(81);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
				
				// send message to client
				webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);

            // send message to client
            // webSocket.sendTXT(num, "message here");

            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    }

}


DHT dht;


void setup(){
    
    Serial.begin(9600);
    dht.setup(D0); 
    
    WiFi.begin("Nombre de tu red", "Password de tu red");
    
    Serial.print("Conectando");
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println();

   Serial.print("Connected, IP address: ");
   Serial.println(WiFi.localIP());

  
   server.on("/", handleRoot);   
   server.begin();                         

   webSocket.begin();
   webSocket.onEvent(webSocketEvent);
}

long timer1 = 0;

void sendInfoTemp(){
            
    long a = millis() - timer1;
    //determina cuando pase un segundo sin parar el resto de procesos //programacion no bloqueante
    
    if(a > 1000 ){
    
        //extrae los valores de la humendad y temperatura
        float h = dht.getHumidity();
        float t = dht.getTemperature();   
        
        //concadena un string con los datos de temperatura y humedad
        webSocket.broadcastTXT(String(h) + "|" + String(t));
        
        //puntero de tiempo
        timer1 = millis();
    }

    
}

void loop(){
    
  //funcion que actualiza el sevidor websocket
  webSocket.loop();  
  //funcion que envia los datos al cliente  cada segundo
  sendInfoTemp();
  //Servidor de pagina web donde se visualizan los datos    
  server.handleClient();     
}