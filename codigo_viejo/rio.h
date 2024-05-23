#include "especie.h"

#ifndef rio_h
#define rio_h

class Rio : public Especie {
public:
  void setup() {
    pinMode(pinSensorRio_n1, INPUT);
    pinMode(pinLuzRio_n1, OUTPUT);
    pinMode(pinReleRio_n1, OUTPUT);
    pinMode(pinReleRio_n2, OUTPUT);
  }

  void desbloquear(int nuevoNivel) {
    if (nuevoNivel == 1) {
      Serial.println("nivel 1 de rio");

      empezarNivel(1);

      // prender las luces del rio 1
      digitalWrite(pinLuzRio_n1, HIGH);

      // delay(5000);  // esperar un poco para bombear el agua? que no sea inmediato

      //activar la bomba de agua 1
      digitalWrite(pinReleRio_n1, HIGH);


      terminarNivel();
    }

    if (nuevoNivel == 2 && nivelTerminado(1)) {
      Serial.println("nivel 2 de rio");
      empezarNivel(2);

      // prender las luces del rio 2
      // digitalWrite(pinLuzRio_n2, HIGH);

      //activar la bomba de agua 2
      digitalWrite(pinReleRio_n2, HIGH);

      terminarNivel();
    }
  }
};

#endif
