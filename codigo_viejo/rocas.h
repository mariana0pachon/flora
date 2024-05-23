#include "especie.h"

#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(pinSSRocas, pinRSTRocas);

// String ID_nivel1 = "16622018095";
String ID_nivel1 = "152188223110"; // caracol 1
String ID_nivel2 = "16622018095"; // caracol 2
String ID_nivel3 = "152163211110";


#ifndef rocas_h
#define rocas_h

class Rocas : public Especie {
public:
  void setup() {
    SPI.begin();
    rfid.PCD_Init();
    pinMode(pinLedsRocas_n1, OUTPUT);
    pinMode(pinLedsRocas_n2, OUTPUT);
  }

  void desbloquear(int nuevoNivel) {
    if (rfid.PICC_IsNewCardPresent()) {
      if (rfid.PICC_ReadCardSerial()) {
        MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
        String uidString = "";

        for (int i = 0; i < rfid.uid.size; i++) {
          uidString += rfid.uid.uidByte[i];
        }

        Serial.println(uidString);

        if (nuevoNivel == 1 && uidString == ID_nivel1) {
          empezarNivel(1);
          // se prenden todas las leds de un color
          Serial.println("Se prenden las rocas nivel 1");
          digitalWrite(pinLedsRocas_n1, HIGH);

          delay(2000);
          terminarNivel();
        }

        if (nuevoNivel == 2 && uidString == ID_nivel2) {
          empezarNivel(2);
          Serial.println("Se prenden las rocas nivel 2");
          digitalWrite(pinLedsRocas_n2, HIGH);
          terminarNivel();
        }

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
      }
    }
  }
};

#endif
