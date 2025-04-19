#include <FastLED.h>
#include "WiFiS3.h"
#include <OSCMessage.h>
#include <SPI.h>
#include <MFRC522.h>

// EL IP DE ESTE ARDUINO ES 192.168.0.102

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
char ssid[] = "Router_Flora";
char pass[] = "Flora666";
// char ssid[] = "WIFIBAU";
// char pass[] = "bau934153474";

unsigned int localPort = 8881;

// IPAddress outIp(192, 168, 0, 119); // mariana innov
// IPAddress outIp(192, 168, 27, 100); // mariana wifi bau
// IPAddress outIp(192, 168, 0, 124);  // daniela wifi innov
IPAddress outIp(192, 168, 1, 35);  // mariana wifi Flora_Router

const unsigned int outPort = 8000;

bool audioSent = false;

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND

#define SS_PIN_1 2
#define RST_PIN_1 3
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);

#define RELE_RIO_PIN 8

// #define LUZ_1_PIN A1

#define NUM_LEDS_RIO 60
#define LED_PIN_RIO 6
#define NUM_LEDS_ROCAS 59
#define LED_PIN_ROCAS 4

CRGB ledsRio[NUM_LEDS_RIO];
CRGB ledsRocas[NUM_LEDS_ROCAS];

bool animarRio = false;
bool animarRocas = false;

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to wifi...");

  WiFi.begin(ssid, pass);
  // while (WiFi.status() != WL_CONNECTED) {
  // delay(500);
  //Serial.println("Retry WiFi connection");
  //}

  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  //Udp.begin(localPort);

  sendConnectionMessage();
  SPI.begin();

  rfid1.PCD_Init();

  pinMode(RELE_RIO_PIN, OUTPUT);
  //pinMode(LUZ_1_PIN, OUTPUT);

  FastLED.addLeds<NEOPIXEL, LED_PIN_RIO>(ledsRio, NUM_LEDS_RIO);
  FastLED.addLeds<NEOPIXEL, LED_PIN_ROCAS>(ledsRocas, NUM_LEDS_ROCAS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  //receiveMessage();

  if (rfid1.PICC_IsNewCardPresent()) {
    Serial.println("lector presente");
    if (rfid1.PICC_ReadCardSerial()) {
      Serial.println("primer nivel caracol");

      //if (!audioSent) sendAudioMessage();

      digitalWrite(RELE_RIO_PIN, HIGH);  // prender la bomba del rio nivel 2
      //digitalWrite(LUZ_1_PIN, HIGH);     // prender las luces nivel 1
      animarRio = true;
      animarRocas = true;

      rfid1.PICC_HaltA();
      rfid1.PCD_StopCrypto1();
    }
  }

  if (animarRio) {
    loopLucesRio();
  }

  if (animarRocas) {
    loopLucesRocas();
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

void receiveMessage() {
  OSCMessage inmsg;              //CREAMOS UNA VARIABLE TIPO OSCMessage (DE LA LIBRERÍA OSC) QUE NOS GUARDA EN UN OBJETO LA INFO DEL MENSAJE
  int size = Udp.parsePacket();  //AQUÍ 'PARSEAMOS' PARA VER EL TAMAÑO DE ESE MENSAJE QUE NOS HEMOS GUARDADO

  if (size > 0) {  //SI EM MENSAJE NO ESTÀ VACIÓ
    while (size--) {
      inmsg.fill(Udp.read());  //VAMOS LLENADO LA VARIABLE DE ATRÁS HACIA DELANTE
    }

    //----------> DESDE AQUÍ HASTA EL FINAL DE LA FUNCIÓN LO PODÉS REPETIR POR CADA MENSAJE
    //POR CADA 'DIRECCION' O NOMBRE DE MENSAJE QUE VAMOS A RECIBIR
    if (!inmsg.hasError()) {            //TENEMOS QUE COMPROBAR QUE NO HAYA ERROR
      inmsg.dispatch("/reset", reset);  //LEERLA Y ASIGNARLE UNA FUNCIÓN DE RESPUESTA
    }
    //----------> ESTE ES EL FINAL DE LA FUNCIÓN A REPETIR POR CADA MENSAJE
  }
}

void reset(OSCMessage &msg) {
  Serial.println("resetting caracol");

  digitalWrite(RELE_RIO_PIN, LOW);
  //digitalWrite(LUZ_1_PIN, LOW);
  animarRio = false;
  animarRocas = false;

  FastLED.clear();  // Instantly turn off LEDs
  FastLED.show();

  audioSent = false;
}

void loopLucesRio() {
  static unsigned long lastUpdate = 0;
  static int index = 0;
  static bool forward = true;
  const unsigned long interval = 20;

  if (millis() - lastUpdate >= interval) {
    // Clear previous LED
    ledsRio[index] = CRGB::Black;

    if (forward) {
      index++;
      if (index >= NUM_LEDS_RIO) {
        index = NUM_LEDS_RIO - 1;
        forward = false;
      }
    } else {
      index--;
      if (index < 0) {
        index = 0;
        forward = true;
      }
    }

    // Set current LED
    ledsRio[index] = CRGB::Blue;
    FastLED.show();
    lastUpdate = millis();
  }
}

void loopLucesRocas() {
  static int currentIndex = 0;
  static unsigned long lastBlinkTime = 0;
  const unsigned long blinkInterval = 150;

  unsigned long now = millis();
  if (now - lastBlinkTime >= blinkInterval) {
    // Turn off the last LED
    ledsRocas[currentIndex] = CRGB::Black;

    // Move to next
    currentIndex = (currentIndex + 1) % NUM_LEDS_ROCAS;

    // Set a new random color
    ledsRocas[currentIndex] = CHSV(random(0, 255), 255, 255);

    FastLED.show();
    lastBlinkTime = now;
  }
}
