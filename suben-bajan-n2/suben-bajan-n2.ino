#include <SPI.h>
#include <MFRC522.h>

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND
#define SS_PIN_3 9
#define RST_PIN_3 8
MFRC522 rfid3(SS_PIN_3, RST_PIN_3);

#define LUZ_3_PIN A5

// Motor para segunda y tercera flor que sube y baja
int motor1Pin1 = 2;
int motor1Pin2 = A0;      // Analog pin used as digital
int motor1Velocidad = 3;  // PWM capable pin
int motor2Pin1 = 4;
int motor2Pin2 = A2;         // Analog pin used as digital
int motor2Velocidad = 5;     // PWM capable pin
int velocidadMotores = 73;  // entre 0 y 255

void setup() {
  Serial.begin(9600);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Velocidad, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Velocidad, OUTPUT);

  rfid3.PCD_Init();
  pinMode(LUZ_3_PIN, OUTPUT);
}

void loop() {
  if (rfid3.PICC_IsNewCardPresent()) {
    if (rfid3.PICC_ReadCardSerial()) {
      Serial.println("segundo nivel caracol");

      digitalWrite(LUZ_3_PIN, HIGH);  // prender las luces nivel 3

      analogWrite(motor1Velocidad, velocidadMotores);
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);

      analogWrite(motor2Velocidad, velocidadMotores);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);

      rfid3.PICC_HaltA();
      rfid3.PCD_StopCrypto1();
    }
  }
}
