#include "WiFiS3.h"
#include <OSCMessage.h>
#include <SPI.h>
#include <MFRC522.h>

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
char ssid[] = "Innovacion";
char pass[] = "Innovacion24";
// char ssid[] = "WIFIBAU";
// char pass[] = "bau934153474";

unsigned int localPort = 8881;

// IPAddress outIp(192, 168, 0, 106); // mariana innov
// IPAddress outIp(192, 168, 27, 100); // mariana wifi bau
IPAddress outIp(192, 168, 0, 124);  // daniela wifi innov

const unsigned int outPort = 8000;

bool audioSent = false;

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND

#define SS_PIN_1 2
#define RST_PIN_1 3
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);

#define RELE_RIO_PIN 8

#define LUZ_1_PIN A1

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
  SPI.begin();

  rfid1.PCD_Init();

  pinMode(RELE_RIO_PIN, OUTPUT);
  pinMode(LUZ_1_PIN, OUTPUT);
}

void loop() {
  if (rfid1.PICC_IsNewCardPresent()) {
    if (rfid1.PICC_ReadCardSerial()) {
      Serial.println("primer nivel caracol");

      if (!audioSent) sendAudioMessage();

      digitalWrite(RELE_RIO_PIN, HIGH);  // prender la bomba del rio nivel 2
      digitalWrite(LUZ_1_PIN, HIGH);     // prender las luces nivel 1

      rfid1.PICC_HaltA();
      rfid1.PCD_StopCrypto1();
    }
  }

  delay(update_rate);  // ESTE ES EL DELAY PARA LA COMUNICACIÓN OSC
}

void sendConnectionMessage() {
  Serial.println("sending connection OSC message...");
  OSCMessage msg("/caracol_connected");
  msg.add(1);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendAudioMessage() {
  Serial.println("sending audio OSC message...");
  OSCMessage msg("/caracol");
  msg.add(123);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  audioSent = true;
}

void reset() {
  digitalWrite(RELE_RIO_PIN, LOW);
  digitalWrite(LUZ_1_PIN, LOW);
}
