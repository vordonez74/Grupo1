#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

//------------Mlx90614------------
#include <Adafruit_MLX90614.h>
//------------Oled------------
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//------------Oled------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//------------Mlx90614------------
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//------------Mlx90614------------
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char* ssid = "ManuMaxi";
const char* password = "vvv4528%%$";
const char* host = "192.168.18.9";

String device = "tarjeta1";
float oxi = 0.0;
float pulso = 0.0;
float temp = 0.0;
int codigo = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Conectando a %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado");    
  //------------Mlx90614------------  
  mlx.begin();  
  //------------Oled------------
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(1000);
  incioValores();
  delay(1000);
  //----------------------------

}

void loop() {
  WiFiClient client;

  Serial.printf("\n[Conectando a %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("conectado]");

    oxi = random(10,90);
    pulso = random(10,90);
    temp = leerTemp();
    actualizarValores(temp,pulso,oxi);
    String getData="dispositivo="+device+"&oxigeno="+String(oxi)+"&pulso="+String(pulso)+"&temperatura="+String(temp);
  
    String url = "/grupo1/carga.php?"+getData;
    
    Serial.println("[Enviando un request]");
    //Serial.println(url);
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
    Serial.println("\n[Desconectado]");
  }
  else
  {
    Serial.println("Falla de conección!]");
    client.stop();
  }
  delay(5000);

}

float leerTemp(){
  //mlx.readAmbientTempC() Ambiente 
  float temp = mlx.readObjectTempC();
  Serial.print(temp); 
  return temp;
}

void actualizarValores(float temp,float pulso, float oxi) {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Bienvenidos! Grupo1"));
  display.setCursor(0,20);
  display.println(F("TEMP.:"));
  display.setTextSize(2);
  display.setCursor(64,15);
  display.println(temp);  
  display.setTextSize(1);
  display.setCursor(0,35);
  display.println(F("PULSO:"));
  display.setCursor(40,35);
  display.println(pulso);  
  display.setCursor(0,50);
  display.println(F("OXIGENO:"));
  display.setTextSize(2);
  display.setCursor(64,50);
  display.println(oxi); 
  display.display();
  delay(2000);
}
void incioValores() {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Bienvenidos! Grupo1"));
  display.setCursor(0,20);
  display.println(F("TEMP.:"));
  display.setTextSize(2);
  display.setCursor(64,15);
  display.println(F("--.--"));  
  display.setTextSize(1);
  display.setCursor(0,35);
  display.println(F("PULSO:"));
  display.setCursor(40,35);
  display.println(F("--.--"));  
  display.setCursor(0,50);
  display.println(F("OXIGENO:"));
  display.setTextSize(2);
  display.setCursor(64,50);
  display.println(F("--.--")); 
  display.display();
  delay(2000);
}