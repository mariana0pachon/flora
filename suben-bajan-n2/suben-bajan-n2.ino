#include "WiFiS3.h"
#include <OSCMessage.h>
#include <SPI.h>
#include <MFRC522.h>

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
// char ssid[] = "Innovacion";
// char pass[] = "Innovacion24";
char ssid[] = "WIFIBAU";
char pass[] = "bau934153474";

unsigned int localPort = 8881;

// IPAddress outIp(192, 168, 0, 106);
IPAddress outIp(192, 168, 27, 100);
const unsigned int outPort = 8000;

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
int motor2Pin2 = A2;        // Analog pin used as digital
int motor2Velocidad = 5;    // PWM capable pin
int velocidadMotores = 73;  // entre 0 y 255

bool audioSent = false;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Retry WiFi connection");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort);

  sendConnectionMessage();

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Velocidad, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Velocidad, OUTPUT);

  rfid3.PCD_Init();
  pinMode(LUZ_3_PIN, OUTPUT);

  analogWrite(motor1Velocidad, velocidadMotores);
  analogWrite(motor2Velocidad, velocidadMotores);
}

void loop() {
  if (rfid3.PICC_IsNewCardPresent()) {
    if (rfid3.PICC_ReadCardSerial()) {
      Serial.println("segundo nivel caracol");

      if (!audioSent) sendAudioMessage();

      digitalWrite(LUZ_3_PIN, HIGH);  // prender las luces nivel 3

      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);

      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);

      rfid3.PICC_HaltA();
      rfid3.PCD_StopCrypto1();
    }
  }

  delay(update_rate);
}

void sendConnectionMessage() {
  Serial.println("sending connection OSC message...");
  OSCMessage msg("/suben_bajan_connected");
  msg.add(1);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendAudioMessage() {
  Serial.println("sending audio OSC message...");
  OSCMessage msg("/suben_bajan");
  msg.add(123);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  audioSent = true;
}
