#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include "MAX30105.h" //MAX30105
#include "spo2_algorithm.h" //MAX30105
#include <Adafruit_MLX90614.h> //Mlx90614
#include <Adafruit_GFX.h> //Oled
#include <Adafruit_SSD1306.h> //Oled

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define MAX_BRIGHTNESS 255 //MAX30105

struct valores{ //MAX30105
    int32_t spo2;
    int32_t heartRate;
};

//MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char* ssid = "ManuMaxi";
//const char* ssid = "HITRON-4320";
const char* password = "vvv4528%%$";
//const char* password = "wifi03r457";
const char* host = "192.168.18.9";
//const char* host = "recursoinformatico.ml";

String device = "tarjeta1";
int32_t oxi = 0.0;
int32_t pulso = 0.0;
float temp = 0.0;
int codigo = 0;
boolean tomarMuestra = false;


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
  Serial.print("[Conectado]");    
  mlx.begin(); //Mlx90614
  
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
  
  //--------MAX30105-----------
  // Inicializar sensor
/*  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println(F("No se encontró MAX30105. Compruebe el cableado o la alimentación."));
    while (1);
  }
  byte ledBrightness = 60;//Options: 0=Off to 255=50mA
  byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2;       //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100;  //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411;   //Options: 69, 118, 215, 411
  int adcRange = 4096;    //Options: 2048, 4096, 8192, 16384
  //Configure el sensor con estos ajustes
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
*/
}

void loop() {
  WiFiClient client;

  Serial.printf("\n[Conectando a %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("[Conectado]");
    if(tomarMuestra){
      /*valores resultado;
      resultado = calcularFCySO2();
      oxi = resultado.spo2;
      pulso = resultado.heartRate;*/
      oxi = 22;
      pulso = 22;
      temp = leerTemp();
    }else{
      oxi = 0;
      pulso = 0;
      temp = 0.0;
    }
    actualizarValores(temp,pulso,oxi);
    String getData="dispositivo="+device+"&oxigeno="+String(oxi)+"&pulso="+String(pulso)+"&temperatura="+String(temp);
  
    String url = "/Grupo1/carga.php?"+getData;
    
    Serial.println("[Enviando un request]");
    
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    
    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String respuesta = client.readStringUntil('\n');
        if(respuesta.substring(0,1)=="{"){
          int ini = respuesta.indexOf(":");
          int fin = respuesta.indexOf("}",ini);
          codigo = respuesta.substring(ini+1,fin).toInt();
          Serial.print("[codigo]");
          Serial.println(codigo);
          if(codigo==1){
            tomarMuestra=true;
            Serial.println("tomará muestra");
          }else{
            tomarMuestra=false;
            Serial.println("no tomará muestra");
          }
        }
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
/*
valores calcularFCySO2(){
    valores resultado;  
    uint32_t irBuffer[100]; //datos del sensor de infrarrojos LED
    uint32_t redBuffer[100];  //datos del sensor LED rojo
    int32_t bufferLength; //longitud de datos
    int32_t spo2; //Valor de SPO2
    int8_t validSPO2; //indicador para mostrar si el cálculo de SPO2 es válido
    int32_t heartRate; //valor de frecuencia cardíaca
    int8_t validHeartRate; //indicador para mostrar si el cálculo de la frecuencia cardíaca es válido
  
    bufferLength = 100; //la longitud del búfer de 100 almacena 4 segundos de muestras que se ejecutan a 25 sps
  
    //leer las primeras 100 muestras y determinar el rango de la señal
    Serial.print("Muestras:");    
    for (byte i = 0 ; i < bufferLength ; i++)
    {
      while (particleSensor.available() == false) //tenemos nuevos datos?
        particleSensor.check(); //Verifique el sensor en busca de nuevos datos
  
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
      Serial.print(".");
    }
    //calcular la frecuencia cardíaca y la SpO2 después de las primeras 100 muestras (primeros 4 segundos de las muestras)
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    resultado.spo2 = spo2;
    resultado.heartRate = heartRate;
    return resultado;      
}
*/
void actualizarValores(float temp,float pulso, float oxi) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
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
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
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
