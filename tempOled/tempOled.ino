#include <SPI.h>
#include <Wire.h>
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
//--------------------------------


Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);  
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
  Serial.print("Ambiente = ");
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "); 
  float temp = mlx.readObjectTempC();
  Serial.print(temp); 
  actualizarValores(temp,0.0,0.0);
  Serial.println("ºC");
  delay(5000);
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
  display.println(F("PLUSO:"));
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
  display.println(F("PLUSO:"));
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
