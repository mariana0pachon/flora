#include "especie.h"

#ifndef flores_suben_h
#define flores_suben_h

class FloresSuben : public Especie {
public:
  void setup() {
    pinMode(floresSubenMotorPin1, OUTPUT);
    pinMode(floresSubenMotorPin2, OUTPUT);

    // Inicializa el motor y realiza cualquier otra configuración necesaria
    floresSubenTiempoInicio = millis();  // Almacena el tiempo actual al inicio
  }

  void desbloquear(int nuevoNivel) {
    if (nuevoNivel == 1) {
      empezarNivel(1);
      // Verifica si han pasado 10 segundos
      if (millis() - floresSubenTiempoInicio >= 10000) {  // 10000 milisegundos = 10 segundos
        // Si han pasado 10 segundos, detén el motor
        digitalWrite(floresSubenMotorPin1, LOW);
        digitalWrite(floresSubenMotorPin2, LOW);
      } else {
        // Si no han pasado 10 segundos, mueve el motor de derecha a izquierda y viceversa
        if (floresSubenDireccion == 1) {
          // Si la dirección es 1, mueve el motor hacia la derecha
          digitalWrite(floresSubenMotorPin1, HIGH);
          digitalWrite(floresSubenMotorPin2, LOW);
        }

        // Espera un tiempo para que el motor se mueva
        delay(1000);  // Cambia este valor según sea necesario
        terminarNivel();
      }
    }
  };

#endif
