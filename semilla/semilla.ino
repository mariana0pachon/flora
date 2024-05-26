#include <SPI.h>
#include <MFRC522.h>

// #define SS_PIN_2 3
// #define RST_PIN_2 4

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND
// MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

#define LUZ_2_PIN A1

int pinSensorHumedad = A0;
int pinReleRio = 8;

// Motor para primera flor que sube y baja
int motorPin1 = 3;
int motorPin2 = 2;

void setup() {
  Serial.begin(9600);

  pinMode(pinSensorHumedad, INPUT);
  pinMode(pinReleRio, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // rfid2.PCD_Init();
  pinMode(LUZ_2_PIN, OUTPUT);
}

void loop() {
  if (analogRead(pinSensorHumedad) > 550) {
    Serial.println("se planto la semilla");

    // enviar senal OSC audio

    digitalWrite(pinReleRio, HIGH);

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

    // despues de un delay, enviar senal OSC mapping para la siguiente instruccion
  }

  // if (rfid2.PICC_IsNewCardPresent()) {
  //   if (rfid2.PICC_ReadCardSerial()) {
  //     Serial.println("tercer nivel caracol");

  //     digitalWrite(LUZ_2_PIN, HIGH);  // prender las luces nivel 2

  //     rfid2.PICC_HaltA();
  //     rfid2.PCD_StopCrypto1();
  //   }
  // }
}
