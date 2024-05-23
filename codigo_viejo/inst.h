#include "especie.h"

#ifndef inst_h
#define inst_h

class Inst : public Especie {
public:
  void setup() {
    pinMode(pinInst1, OUTPUT);
    pinMode(pinInst2, OUTPUT);
    pinMode(pinInst3, OUTPUT);
    pinMode(pinInst4, OUTPUT);
  }

  void darInstruccion(int nivel) {
    if (nivel == 1) {
      digitalWrite(pinInst1, HIGH);
      digitalWrite(pinInst2, LOW);
      digitalWrite(pinInst3, LOW);
      digitalWrite(pinInst4, LOW);
    }
    if (nivel == 2) {
      digitalWrite(pinInst1, LOW);
      digitalWrite(pinInst2, HIGH);
      digitalWrite(pinInst3, LOW);
      digitalWrite(pinInst4, LOW);
    }
    if (nivel == 3) {
      digitalWrite(pinInst1, LOW);
      digitalWrite(pinInst2, LOW);
      digitalWrite(pinInst3, HIGH);
      digitalWrite(pinInst4, LOW);
    }
    if (nivel == 4) {
      digitalWrite(pinInst1, LOW);
      digitalWrite(pinInst2, LOW);
      digitalWrite(pinInst3, LOW);
      digitalWrite(pinInst4, HIGH);
    }
  }
};

#endif