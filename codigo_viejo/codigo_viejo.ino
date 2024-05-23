#include <Arduino.h>

#include "pines.h"
#include "rio.h"
#include "rocas.h"
#include "inst.h"

Rio rio;
Rocas rocas;
Inst inst;

int humedadAnterior;

void setup() {
  Serial.begin(9600);

  rio.setup();
  rocas.setup();
  inst.setup();

  humedadAnterior = analogRead(pinSensorRio_n1);

  inst.darInstruccion(1);
}

void loop() {
  // Serial.print("humedadAnterior: ");
  // Serial.println(humedadAnterior);
  // Serial.print("humedad actual: ");
  // Serial.println(analogRead(pinSensorRio_n1));

  // if (analogRead(pinSensorRio_n1) > humedadAnterior + 10) {  // margen de 10 para que no se active tan facilmente
  if (analogRead(pinSensorRio_n1) > 550) {
    humedadAnterior = analogRead(pinSensorRio_n1);
    rio.desbloquear(1);
    // TODO: empezar nivel de flores que suben 1
  }

  if (rio.nivelTerminado(1) && !rocas.nivelTerminado(1)) { // esto esta muy chirri, hay que encontrar una mejor forma de no siempre prender la luz
    inst.darInstruccion(2);
    rocas.desbloquear(1);
  }

  if (rocas.nivelTerminado(1)) {
    inst.darInstruccion(3);
    inst.darInstruccion(4);

    rio.desbloquear(2);
    // TODO: empezar nivel de flores que suben 2

    rocas.desbloquear(2);
    rocas.desbloquear(3);
  }
}
