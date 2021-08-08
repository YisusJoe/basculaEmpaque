#include "HX711.h"

#define calibration_factor -22000//-44

#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3
#define BOX 4
#define BOXSUM 5

float Lecturas[5];
float mass = 0;
float Total = 0;
float  Val = 0;
int i = 0;

HX711 scale;

void setup() {
  Serial.begin(9600);
  pinMode(BOX, INPUT);
  pinMode(BOXSUM, INPUT);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(calibration_factor);
  scale.tare();

  for (i = 0; i < 5; i++) {
    Lecturas[i] = 0;
    //Serial.println(i);
    //i=0;
  }

  Serial.println("Iniciando llenadora");
  delay(1000);
  Serial.print('.');
  delay(1000);
  Serial.print('.');
  delay(1000);
  Serial.println('.');
  delay(1000);
}

void loop() {
  int box = digitalRead(BOX);
  //Serial.println(box);
  Serial.print("¿Hay una caja en la bàscula?    ");
  //delay(1000);

  if (box == 1) {
    Serial.print("Si hay una caja en la báscula    ");
    Serial.println("Banda apagada");
    //delay(1000);
    mass = 0;
    while (mass < 35 and box == 1) {
      //Serial.println("Encender banda tomates");
      mass = masa();
      Serial.print("Si hay una caja en la báscula    ");
      Serial.print("Banda encendida    ");
      Serial.println(mass);
      //delay(500);

      if(mass>=33){
        Serial.println("LANZAR CAJA");
      }
    }
//    Serial.println("Sali");
//    delay(1000);
  } else {
    Serial.println("No hay caja en la báscula");
  }
}

float masa() {
  //Serial.println("Iniciando lecturas");

  Total = Total - Lecturas[i];
  Lecturas[i] = scale.get_units();
  Total = Total + Lecturas[i];
  i = i + 1 ;

  if (i >= 5) {
    i = 0;
    mass = Total / 5;

    if (mass < 0.5) {
      mass = 0.0;
    }

    return mass;
    //    Serial.print(mass,1);
    //    Serial.print(" g");
    //    Serial.println();
  }
}