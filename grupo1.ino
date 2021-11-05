#include "lib_ejc.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

String url = "http://192.168.18.9/grupo1/carga.php";

String device = "tarjeta1";

float oxi = 0.0;
float pulso = 0.0;
float temp = 0.0;
int led = 0;

void setup() {
  conectarWiFi_EJC();
}

void loop() {
  HTTPClient http;
  WiFiClient client;
  http.begin(client, url);
  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  oxi = random(10,90);
  pulso = random(10,90);
  temp = random(1,60);
    
  String postData="dispositivo="+device+"&oxigeno="+String(oxi)+"&pulso="+String(pulso)+"&temperatura="+String(temp);
  
  int httpCode = http.POST(postData); //Send the request
  String respuesta = http.getString(); //Get the response payload

  //Serial.println(httpCode);
  Serial.println(respuesta);

  int ini = respuesta.indexOf(":");
  int fin = respuesta.indexOf("}",ini);
  led = respuesta.substring(ini+1,fin).toInt();

  
  http.end(); //close connection
  delay(10000);
}
