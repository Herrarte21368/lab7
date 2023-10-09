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

//*****************************************************************************
// Definición de pines
//*****************************************************************************

int pot2 = A0;

// Pines de los botones
int botonIncrementar = 3; // Reemplaza con el pin correcto
int botonDecrementar = 4; // Reemplaza con el pin correcto
int ledPinB = 5;
int ledPinG = 6;

//*****************************************************************************
// Prototipos de función
//*****************************************************************************
//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
uint8_t decenas, unidades, decimal;
int adcRaw;
float voltaje;
uint8_t contador = 0; // Contador de 8 bits

char cont[4];
String strRed; //Convertir en Cadena

//*****************************************************************************
// Configuración
//*****************************************************************************
void setup() {
  Serial.begin(9600);
  // Inicializa la pantalla LCD
  // Configura los pines de los botones como entradas con pull-up
  pinMode(botonIncrementar, INPUT_PULLUP);
  pinMode(botonDecrementar, INPUT_PULLUP);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  // Inicializa el contador en 0
  //contador = 0;
  //mostrar el valor incial del contador en la pantalla LCD
}

//*****************************************************************************
// Loop Principal
//*****************************************************************************
void loop() {

  // Lee el valor del potenciómetro 2
  voltaje = analogRead(pot2) / 10.0;
  int brightness = map(voltaje, 0, 1023, 0, 255);  // Mapea el valor a un rango de brillo (0-255)
  analogWrite(ledPinB, brightness);  // Establece el brillo del LED
  int temp2 = voltaje;
  decenas = temp2 / 100.0;
  temp2 = temp2 - decenas * 100.0;
  unidades = temp2 / 10.0;
  temp2 = temp2 - unidades * 10.0;
  decimal = temp2;
  delay(250);

  // Verifica si se presionó el botón de incremento
  if (digitalRead(botonIncrementar) == LOW) {
    if (contador < 255) { // Asegúrate de que el contador no supere 255
      contador++;
      analogWrite(ledPinG, contador); // Actualiza el brillo del primer LED
      delay(200); // Evita el rebote del botón
    }
  }

  // Verifica si se presionó el botón de decremento
  if (digitalRead(botonDecrementar) == LOW) {
    if (contador > 0) { // Asegúrate de que el contador no sea negativo
      contador--;
      analogWrite(ledPinG, contador); // Actualiza el brillo del primer LED
      delay(200); // Evita el rebote del botón
    }
  }

  strRed = contador;
  strRed.toCharArray(cont,4); //Convertir string a char
    Serial.write(cont);
    Serial.print('\n');

}
