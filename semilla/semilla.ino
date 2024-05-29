// #include <SPI.h>
// #include <MFRC522.h>
#include "WiFiS3.h"
#include <OSCMessage.h>

// #define SS_PIN_2 3
// #define RST_PIN_2 4

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND
// MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

WiFiUDP Udp;
int update_rate = 16;          //ESTE ES EL DELAY DE ACTUALIZACIÓN DE RECEPCIÓN DE DATOS OSC
char ssid[] = "WIFIBAU";       // Cambiar a la red del router
char pass[] = "bau934153474";  // Cambiar a la clave del router

IPAddress outIp(127, 0, 0, 1);      // IP a la que queremos enviar mensajes (localhost porque Processing corre en este mismo compu)
const unsigned int outPort = 8888;  // Puerto que escucha en el otro dispositivo

#define LUZ_2_PIN A1

int pinSensorHumedad = A0;
int pinReleRio = 8;

// Motor para primera flor que sube y baja
int motorPin1 = 3;
int motorPin2 = 2;
int motorPinVelocidad = 6;

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

  pinMode(pinSensorHumedad, INPUT);
  pinMode(pinReleRio, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPinVelocidad, OUTPUT);

  // rfid2.PCD_Init();
  pinMode(LUZ_2_PIN, OUTPUT);
}

void loop() {
  if (analogRead(pinSensorHumedad) > 550) {
    Serial.println("se planto la semilla");

    // enviar senal OSC audio
    sendAudioMessage();

    digitalWrite(pinReleRio, HIGH);


    analogWrite(motorPinVelocidad, 100);
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

  delay(update_rate);  // ESTE ES EL DELAY PARA LA COMUNICACIÓN OSC
}

void sendConnectionMessage() {
  Serial.println("sending connection OSC message...");
  OSCMessage msg("/connected");  // LE PASO EL MENSAJE COMO STRING
  msg.add(1);                    //LE AÑADO EL VALOR QUE QUIERO ENVIAR POR EL MENSAJE

  Udp.beginPacket(outIp, outPort);  //ME CONECTO AL DISPOSITIVO DEFINIDO ARRIBA EN IP Y PUERTO
  msg.send(Udp);                    //ENVIAMOS EL MENSAJE POR PROTOCOLO UDP

  //ESTAS DOS ULTIMAS ACCIONES CIERRAN LA COMUNICACIÓN PARA QUE NO QUEDE ABIERTA Y DE PROBLEMAS
  Udp.endPacket();
  msg.empty();
}

void sendAudioMessage() {
  OSCMessage msg("/audio");  // LE PASO EL MENSAJE COMO STRING
  msg.add("semilla");        //LE AÑADO EL VALOR QUE QUIERO ENVIAR POR EL MENSAJE

  Udp.beginPacket(outIp, outPort);  //ME CONECTO AL DISPOSITIVO DEFINIDO ARRIBA EN IP Y PUERTO
  msg.send(Udp);                    //ENVIAMOS EL MENSAJE POR PROTOCOLO UDP

  //ESTAS DOS ULTIMAS ACCIONES CIERRAN LA COMUNICACIÓN PARA QUE NO QUEDE ABIERTA Y DE PROBLEMAS
  Udp.endPacket();
  msg.empty();
}
