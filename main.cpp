//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Andrée Herrarte 
// Laboratorio 5
//*****************************************************************************
//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "driver/ledc.h"
//*****************************************************************************
// Definición de pines
//*****************************************************************************
#define d4 14
#define d5 27
#define d6 26
#define d7 25
#define en 12
#define rs 13
#define pot 34
#define pot2 35


//parametros de lla senal PWM 
#define ledRChannel 1
#define freqPWM1 5000 //frecuencia en Hz 
#define resolution 8
#define pinLedR 5

int verde;
//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
int adcRaw;
float voltaje;

//*****************************************************************************
// Prototipos de función
//*****************************************************************************
void configurarPWM(void);
//*****************************************************************************
// Configuración
//*****************************************************************************
void setup() {
  Serial.begin(9600);

  // Inicializa la pantalla LCD
  LCD.begin(16, 2);

  pinMode(pinLedR, OUTPUT);
  //pinMode(pinLedG, OUTPUT);
  configurarPWM();
  
}

//*****************************************************************************
// Loop Principal
//*****************************************************************************

void loop() {
  // Lee el valor del potenciómetro 1
  voltaje = analogReadMilliVolts(pot) / 10.0;
  int brilloledR = map(voltaje, 0, 1023, 0, 255);
  int temp = voltaje;
  decenas = temp / 100.0;
  temp = temp - decenas * 100.0;
  unidades = temp / 10.0;
  temp = temp - unidades * 10.0;
  decimal = temp;
  LCD.setCursor(0, 0);
  LCD.print("Rojo");
  LCD.setCursor(0, 1);
  LCD.print(decenas);
  LCD.print('.');
  LCD.print(unidades);
  LCD.print(decimal);

  

  ledcWrite(ledRChannel, brilloledR); 
  
  if(Serial.available()>0)
  {
    String entrada = Serial.readStringUntil('\n');	// lectura de datos
    verde = entrada.toInt(); //Convertir string a int

    LCD.setCursor(12, 0);
    LCD.print("CPU");
    LCD.setCursor(12, 1);
    LCD.print(verde);
  }

}

void configurarPWM(void){

  ledcSetup(ledRChannel, freqPWM1, resolution);

  ledcAttachPin(pinLedR, ledRChannel);


}
