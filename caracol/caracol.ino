#include <SPI.h>
#include <MFRC522.h>

#include "WiFiS3.h"
#include <OSCMessage.h>

WiFiUDP Udp;
int update_rate = 16;          //ESTE ES EL DELAY DE ACTUALIZACIÓN DE RECEPCIÓN DE DATOS OSC
char ssid[] = "WIFIBAU";       // Cambiar a la red del router
char pass[] = "bau934153474";  // Cambiar a la clave del router

IPAddress outIp(192, 168, 26, 203);  // IP a la que queremos enviar mensajes (Processing)
const unsigned int outPort = 8888;   // Puerto que escucha en el otro dispositivo

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND

#define SS_PIN_1 2
#define RST_PIN_1 3
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);

#define RELE_RIO_PIN 8

#define LUZ_1_PIN A0

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  // Probar conexion hasta que funcione
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Retry WiFi connection");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // INCLUYENDO EL NÚMERO DE IP QUE SE NOS HA ASIGNADO
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

      // enviar senal OSC audio
      sendAudioMessage();

      digitalWrite(RELE_RIO_PIN, HIGH);  // prender la bomba del rio nivel 2
      digitalWrite(LUZ_1_PIN, HIGH);     // prender las luces nivel 1

      rfid1.PICC_HaltA();
      rfid1.PCD_StopCrypto1();
    }
  }

  delay(update_rate);  // ESTE ES EL DELAY PARA LA COMUNICACIÓN OSC
}

void sendConnectionMessage() {
  OSCMessage msg("/connected");  // LE PASO EL MENSAJE COMO STRING
  msg.add("caracol");            //LE AÑADO EL VALOR QUE QUIERO ENVIAR POR EL MENSAJE

  Udp.beginPacket(outIp, outPort);  //ME CONECTO AL DISPOSITIVO DEFINIDO ARRIBA EN IP Y PUERTO
  msg.send(Udp);                    //ENVIAMOS EL MENSAJE POR PROTOCOLO UDP

  //ESTAS DOS ULTIMAS ACCIONES CIERRAN LA COMUNICACIÓN PARA QUE NO QUEDE ABIERTA Y DE PROBLEMAS
  Udp.endPacket();
  msg.empty();
}

void sendAudioMessage() {
  OSCMessage msg("/audio");  // LE PASO EL MENSAJE COMO STRING
  msg.add("caracol");        //LE AÑADO EL VALOR QUE QUIERO ENVIAR POR EL MENSAJE

  Udp.beginPacket(outIp, outPort);  //ME CONECTO AL DISPOSITIVO DEFINIDO ARRIBA EN IP Y PUERTO
  msg.send(Udp);                    //ENVIAMOS EL MENSAJE POR PROTOCOLO UDP

  //ESTAS DOS ULTIMAS ACCIONES CIERRAN LA COMUNICACIÓN PARA QUE NO QUEDE ABIERTA Y DE PROBLEMAS
  Udp.endPacket();
  msg.empty();
}
