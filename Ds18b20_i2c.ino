/* 
 criado por: Domingos R Souza Junior
 blog: sistemasinterativoscomarduino.net
*/

#include <OneWire.h>                  // bilioteca OneWire
#include <Wire.h>                     // usando a biblioteca Wire
#include <LiquidCrystal_I2C.h>        // usando a biblioteca LiquidCrystal I2C
#include <DallasTemperature.h>        // usando a biblioteca DallasTemperature

#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

// Configura endereço I2C e display com 16 caracteres e 2 linhas 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 
 
void setup()
{
  Serial.begin(9600);
  sensors.begin();                      // inicializa o sensor
  lcd.begin(16,2);                      // inicializa LCD
  lcd.backlight();  
  pinMode(8, OUTPUT);   
  pinMode(12, OUTPUT);
}

void displaytemperatura(int indicesensor)
{
  lcd.clear();
  float temp = sensors.getTempCByIndex(indicesensor); // Envie o comando para obter leituras de temperatura
  lcd.setCursor(0,0);
  lcd.print(temp,1);
  lcd.write(B11011111); // imprime o simbolo de grau
  lcd.print("C");
  lcd.setCursor(0,1);
  if (temp > 30 && temp < 20){
    lcd.println("Alert");
    digitalWrite(8, HIGH);
  }else{
    digitalWrite(8,LOW);
  }
  if ((temp < 20) || (temp > 30)){
    digitalWrite(8, HIGH);
    digitalWrite(12, HIGH);
    lcd.print("TempAnormal");
  }else{
    digitalWrite(8,LOW);
    digitalWrite(12,LOW);
  }
}

void loop()
{
  sensors.requestTemperatures();
  displaytemperatura(0); //chama a função que lê o sensor e exibe a mensagem na tela do LCD
  delay(2000);
}