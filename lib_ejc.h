#include <ESP8266WiFi.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <Ticker.h>
#define pinLedWifi D4
//Instancia a la clase Ticker
Ticker ticker;

void parpadeoLedWifi(){
  byte estado = digitalRead(pinLedWifi);
  digitalWrite(pinLedWifi, !estado);
}

void conectarWiFi_EJC(){
Serial.begin(115200);

  pinMode(pinLedWifi, OUTPUT);
  //Empezamos el temporizador que hará parpadear el LED
  ticker.attach(0.2, parpadeoLedWifi);
  
  //Creamos una instancia de la calse wifiManager
  WiFiManager wifiManager;
  
  //Descomentar para resetear configuración
  //wifiManager.resetSettings();

  //Creamos AP y portal cautivo
  if(!wifiManager.autoConnect("ESP8266_GRUPO1")){
    Serial.println("Fallo en la conexión");
    ESP.reset();
    delay(1000);
  }

  Serial.println("Ya está conectado");
  //Eliminamos el temporizador
  ticker.detach();
  //Apagamos el LED
  digitalWrite(pinLedWifi, HIGH);  
}