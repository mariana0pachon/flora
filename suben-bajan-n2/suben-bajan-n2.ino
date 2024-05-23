#include <SPI.h>
#include <MFRC522.h>

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND
#define SS_PIN_3 6
#define RST_PIN_3 7
MFRC522 rfid3(SS_PIN_3, RST_PIN_3);

#define LUZ_3_PIN A5

// Motor para segunda y tercera flor que sube y baja
int motor1Pin1 = 2;
int motor1Pin2 = 4;
int motor2Pin1 = 9;
int motor2Pin2 = 8;

void setup() {
  Serial.begin(9600);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  rfid3.PCD_Init();
  pinMode(LUZ_3_PIN, OUTPUT);
}

void loop() {
  // if (senal OSC fue recibida)
  Serial.println("recibida senal OSC");

  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  // }

  if (rfid3.PICC_IsNewCardPresent()) {
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
