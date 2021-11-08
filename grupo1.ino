#include <ESP8266WiFi.h>

const char* ssid = "HITRON-4320";
//ManuMaxi-vvv4528%%$
const char* password = "wifi03r457";

const char* host = "192.168.0.20";

String device = "tarjeta1";

float oxi = 0.0;
float pulso = 0.0;
float temp = 0.0;
int codigo = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

    oxi = random(10,90);
    pulso = random(10,90);
    temp = random(1,60);
    String getData="dispositivo="+device+"&oxigeno="+String(oxi)+"&pulso="+String(pulso)+"&temperatura="+String(temp);
  
    String url = "/grupoAle2/carga.php?"+getData;
    
    Serial.println("[Sending a request]");
    Serial.println(url); // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    
    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String respuesta = client.readStringUntil('\n');
        Serial.println(respuesta);
        int ini = respuesta.indexOf(":");
        int fin = respuesta.indexOf("}",ini);
        codigo = respuesta.substring(ini+1,fin).toInt();
        Serial.println(codigo);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(25000);
}