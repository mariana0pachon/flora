#include <FastLED.h>
#include "WiFiS3.h"
#include <OSCMessage.h>

// EL IP DE ESTE ARDUINO ES 192.168.0.121

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

// #define LUZ_2_PIN A1

#define NUM_LEDS_RIO 60
#define LED_PIN_RIO 11

CRGB ledsRio[NUM_LEDS_RIO];
bool animarRio = false;

int pinSensorHumedad = A0;
int pinReleRio = 8;
int motorPin1 = 3;
int motorPin2 = 2;
int motorPinVelocidad = 6;

bool audioSent = false;
bool semillaPlantada = false;

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

  pinMode(pinSensorHumedad, INPUT);
  pinMode(pinReleRio, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPinVelocidad, OUTPUT);

  analogWrite(motorPinVelocidad, 100);

  // pinMode(LUZ_2_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, LED_PIN_RIO>(ledsRio, NUM_LEDS_RIO);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Serial.println(WiFi.localIP());

  // delay(5000);
  // Serial.println();
  // sendAudioMessage();

  //Serial.println("in loop");
  receiveMessage();

  Serial.println(analogRead(pinSensorHumedad));

  if (analogRead(pinSensorHumedad) > 90) {
    semillaPlantada = true;
  } else {
    semillaPlantada = false;
  }

  if (semillaPlantada) {
    // Serial.println("se planto la semilla");

    if (!audioSent) sendAudioMessage();

    digitalWrite(pinReleRio, HIGH);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

    animarRio = true;
  }

  if (animarRio) {
    loopLucesRio();
  }
  delay(update_rate);
}

void sendConnectionMessage() {
  Serial.println("sending connection OSC message...");
  OSCMessage msg("/semilla_connected");
  msg.add(1);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendAudioMessage() {
  Serial.println("sending audio OSC message...");
  OSCMessage msg("/semilla");
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
  Serial.println("resetting semilla");
  semillaPlantada = false;
  audioSent = false;
  digitalWrite(pinReleRio, LOW);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  animarRio = false;

  FastLED.clear();  // Instantly turn off LEDs
  FastLED.show();
}

void loopLucesRio() {
  static unsigned long lastUpdate = 0;
  static int index = 0;
  static bool forward = true;
  const unsigned long interval = 60;  // Slower = smoother
  const float fadeWidth = 8.0;

  if (millis() - lastUpdate >= interval) {
    // Move the pulse
    if (forward) {
      index++;
      if (index >= NUM_LEDS_RIO + fadeWidth) {
        index = NUM_LEDS_RIO + fadeWidth - 1;
        forward = false;
      }
    } else {
      index--;
      if (index < -fadeWidth) {
        index = -fadeWidth;
        forward = true;
      }
    }

    for (int i = 0; i < NUM_LEDS_RIO; i++) {
      float distance = abs(i - index);
      float brightness = 1.0 - (distance / fadeWidth);
      brightness = constrain(brightness, 0.05, 1.0);  // minimum background glow

      uint8_t r = 20 * brightness;
      uint8_t g = 100 * brightness;
      uint8_t b = 250 * brightness;

      ledsRio[i] = CRGB(r, g, b);
    }

    FastLED.show();
    lastUpdate = millis();
  }
}
