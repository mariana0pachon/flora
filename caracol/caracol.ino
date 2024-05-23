#include <SPI.h>
#include <MFRC522.h>

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND

#define SS_PIN_1 10
#define RST_PIN_1 2
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);

#define SS_PIN_2 3
#define RST_PIN_2 4
MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

#define SS_PIN_3 6
#define RST_PIN_3 7
MFRC522 rfid3(SS_PIN_3, RST_PIN_3);

#define RELE_RIO_PIN 8

#define LUZ_1_PIN A0
#define LUZ_2_PIN A1
#define LUZ_3_PIN A5

void setup() {
  Serial.begin(9600);

  SPI.begin();

  rfid1.PCD_Init();
  rfid2.PCD_Init();
  rfid3.PCD_Init();

  pinMode(RELE_RIO_PIN, OUTPUT);
  pinMode(LUZ_1_PIN, OUTPUT);
}

void loop() {
  if (rfid1.PICC_IsNewCardPresent()) {
    if (rfid1.PICC_ReadCardSerial()) {
      Serial.println("primer nivel caracol");

      // enviar señal OSC para activar audio caracoles

      digitalWrite(RELE_RIO_PIN, HIGH);  // prender la bomba del rio nivel 2
      digitalWrite(LUZ_1_PIN, HIGH);     // prender las luces nivel 1

      rfid1.PICC_HaltA();
      rfid1.PCD_StopCrypto1();
    }
  }

  else if (rfid2.PICC_IsNewCardPresent()) {
    if (rfid2.PICC_ReadCardSerial()) {
      Serial.println("segundo nivel caracol");

      digitalWrite(LUZ_2_PIN, HIGH);  // prender las luces nivel 2

      rfid2.PICC_HaltA();
      rfid2.PCD_StopCrypto1();
    }
  }

  else if (rfid3.PICC_IsNewCardPresent()) {
    if (rfid3.PICC_ReadCardSerial()) {
      Serial.println("tercer nivel caracol");

      digitalWrite(LUZ_3_PIN, HIGH);  // prender las luces nivel 3

      // enviar senal OSC al arduino suben-bajan-n2 para activar esas flores
      // despues de un delay enviar señal OSC para activar mapping 2

      rfid3.PICC_HaltA();
      rfid3.PCD_StopCrypto1();
    }
  }
}
