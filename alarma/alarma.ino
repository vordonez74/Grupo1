#define buzzer_pin 14 //Define buzzer pin 

void setup()
{
  pinMode(buzzer_pin,OUTPUT);
}
 
void loop()
{
  for(int i=200;i<=800;i++)  //Increase frequency from 200HZ to 800HZ in a circular manner.
  {
    tone(buzzer_pin,i);    //Output frequency in Number four port. 
    delay(5);      //The frequency lasts 5ms. 
  }
  delay(2000);     //The highest frequency lasts 2s.
  for(int i=800;i>=200;i--)
  {
    tone(buzzer_pin,i);
    delay(10); //The frequency lasts 10ms. 
  }
}
