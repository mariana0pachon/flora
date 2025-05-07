#include <FastLED.h>
#include "WiFiS3.h"
#include <OSCMessage.h>
#include <SPI.h>
#include <MFRC522.h>

// EL IP DE ESTE ARDUINO FIJO EN ROUTER FLORA ES 192.168.1.39

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

// los lectores RFID comparten ademas los pines 13, 11, 12, 3.3V, GND
#define SS_PIN_3 9
#define RST_PIN_3 8
MFRC522 rfid3(SS_PIN_3, RST_PIN_3);

// #define LUZ_3_PIN A5
#define NUM_LEDS_ROCAS 15
#define LED_PIN_ROCAS_1 6
#define LED_PIN_ROCAS_2 7

CRGB ledsRocas1[NUM_LEDS_ROCAS];
CRGB ledsRocas2[NUM_LEDS_ROCAS];
bool animarRocas = false;

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

  SPI.begin();
  rfid3.PCD_Init();
  Serial.println("RFID reader initialized");
  // pinMode(LUZ_3_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, LED_PIN_ROCAS_1>(ledsRocas1, NUM_LEDS_ROCAS);
  FastLED.addLeds<NEOPIXEL, LED_PIN_ROCAS_2>(ledsRocas2, NUM_LEDS_ROCAS);
  FastLED.clear();
  FastLED.show();

  analogWrite(motor1Velocidad, velocidadMotores);
  analogWrite(motor2Velocidad, velocidadMotores);
}

void loop() {
  receiveMessage();

  if (rfid3.PICC_IsNewCardPresent()) {
    Serial.println("new card present");
    if (rfid3.PICC_ReadCardSerial()) {
      Serial.println("segundo nivel caracol");

      if (!audioSent) sendAudioMessage();

      // digitalWrite(LUZ_3_PIN, HIGH);  // prender las luces nivel 3
      animarRocas = true;

      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);

      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);

      rfid3.PICC_HaltA();
      rfid3.PCD_StopCrypto1();
    }
  }

  if (animarRocas) {
    loopLucesRocas();
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
  Serial.println("resetting suben bajan");

  // digitalWrite(LUZ_3_PIN, LOW);

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

  audioSent = false;

  animarRocas = false;
  FastLED.clear();  // Instantly turn off LEDs
  FastLED.show();
}

void loopLucesRocas() {
  static unsigned long lastBlinkTime = 0;
  const unsigned long blinkInterval = 150;

  unsigned long now = millis();
  if (now - lastBlinkTime >= blinkInterval) {
    // Turn off the last LED
    for (int i = 0; i < NUM_LEDS_ROCAS; i++) {
      ledsRocas1[i] = CRGB::Black;
      ledsRocas2[i] = CRGB::Black;
    }

    for (int i = 0; i < NUM_LEDS_ROCAS; i++) {
      CRGB color = CHSV(random(0, 255), 255, 255);
      ledsRocas1[i] = color;
      ledsRocas2[i] = color;
    }

    FastLED.show();
    lastBlinkTime = now;
  }
}
