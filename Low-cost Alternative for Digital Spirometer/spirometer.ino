#include <Wire.h>
#include <LiquidCrystal_I2C.h>
float sensor = A0;
float valueSensor;
float value;
float pressure;
float arr[100];
float temp=0.0;
int i=0;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Blow your First Blow");
  lcd.setCursor(4,1);
  lcd.print("Blow");
  delay(4000);
}
float average(float avr, float i)
{
  float jk;
  jk=avr/i;
  return jk;
}
void loop()
{
  float aug;
  valueSensor = analogRead(sensor);
  value = valueSensor ;
  pressure=map(value,0,1023,0,1020);
  Serial.print(" Sensor Raw Value:");
  Serial.print(valueSensor);
  Serial.print("\n");
  Serial.print("Pressure Calibrated:");
   Serial.print (pressure); 
  if(pressure>10)
  {
    arr[i]=pressure;
   temp=temp+arr[i];
    i=i+1;
  }
  lcd.print("               ");
  Serial.println(aug);
  lcd.setCursor(0,1);
  lcd.print("            ");
  lcd.setCursor(0,0);
  lcd.print(aug);
  delay(3000);
}
