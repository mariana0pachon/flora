#include <SPI.h>
#include <MFRC522.h>

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND

#define SS_PIN_1 10
#define RST_PIN_1 2
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);

#define RELE_RIO_PIN 8

#define LUZ_1_PIN A0

void setup() {
  Serial.begin(9600);

  SPI.begin();

  rfid1.PCD_Init();

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
}
