#include <FastLED.h>
#include <ezButton.h>
#include <Stepper.h>
#include "WiFiS3.h"
#include <OSCMessage.h>

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
char ssid[] = "Innovacion";
char pass[] = "Innovacion24";

unsigned int localPort = 8881;

IPAddress outIp(192, 168, 0, 106);
const unsigned int outPort = 8000;

bool climaxAudioSent = false;

// *** PINES 5, 6, 8 ya estan cogidos para las LEDS ***

// Motor para flores giratorias
int stepsPerRevolution = 2048;  // steps per revolution

Stepper stepper(stepsPerRevolution, 9, 11, 12, 13);  // los 4 pines IN

int pinBoton1 = 2;
int pinBoton2 = 3;
int pinBoton3 = 4;

int debounceTime = 50;  // En milisegundos

// Crear un ezButton object para cada uno de los limit switches
ezButton limitSwitch1(pinBoton1);
ezButton limitSwitch2(pinBoton2);
ezButton limitSwitch3(pinBoton3);

// Definimos las tiras de led que tienen 1 solo led
CRGB leds1[1];
CRGB leds2[1];
CRGB leds3[1];

// Estados de colores de leds
String led1State = "black";
String led2State = "black";
String led3State = "black";

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
  // Inicializamos los pines de los LEDs como salidas
  FastLED.addLeds<NEOPIXEL, 5>(leds1, 1);  // pin 5
  FastLED.addLeds<NEOPIXEL, 6>(leds2, 1);  // pin 6
  FastLED.addLeds<NEOPIXEL, 8>(leds3, 1);  // pin 8

  limitSwitch1.setDebounceTime(debounceTime);
  limitSwitch2.setDebounceTime(debounceTime);
  limitSwitch3.setDebounceTime(debounceTime);

  stepper.setSpeed(5);  // rpm
}

void loop() {
  limitSwitch1.loop();
  limitSwitch2.loop();
  limitSwitch3.loop();

  if (limitSwitch1.isPressed()) {
    sendAbejasAudioMessage();

    if (led1State == "black") {
      leds1[0] = CRGB::White;
      led1State = "white";
    } else if (led1State == "white") {
      leds1[0] = CRGB::Red;
      led1State = "red";
    } else {
      leds1[0] = CRGB::Black;
      led1State = "black";
    }

    Serial.print("flor 1 se toco, ahora esta de color: ");
    Serial.println(led1State);
  }

  if (limitSwitch2.isPressed()) {
    sendAbejasAudioMessage();

    if (led2State == "black") {
      leds2[0] = CRGB::White;
      led2State = "white";
    } else if (led2State == "white") {
      leds2[0] = CRGB::Red;
      led2State = "red";
    } else {
      leds2[0] = CRGB::Black;
      led2State = "black";
    }

    Serial.print("flor 2 se toco, ahora esta de color: ");
    Serial.println(led2State);
  }

  if (limitSwitch3.isPressed()) {
    // enviar senal OSC de audio
    sendAbejasAudioMessage();

    if (led3State == "black") {
      leds3[0] = CRGB::White;
      led3State = "white";
    } else if (led3State == "white") {
      leds3[0] = CRGB::Red;
      led3State = "red";
    } else {
      leds3[0] = CRGB::Black;
      led3State = "black";
    }

    Serial.print("flor 3 se toco, ahora esta de color: ");
    Serial.println(led3State);
  }

  FastLED.show();

  // Cuando las 3 leds esten en su estado final ya "polinizado" prender el motor de las flores giratorias
  if (led1State == "red" && led2State == "red" && led3State == "red") {
    Serial.println("Prender flores giratorias");

    stepper.step(stepsPerRevolution);

    if (!climaxAudioSent) sendClimaxAudioMessage();
  }

  delay(update_rate);
}

void sendConnectionMessage() {
  Serial.println("sending connection OSC message...");
  OSCMessage msg("/abejas_connected");
  msg.add(1);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendAbejasAudioMessage() {
  Serial.println("sending audio OSC message...");
  OSCMessage msg("/abejas");
  msg.add(123);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendClimaxAudioMessage() {
  Serial.println("sending audio OSC message...");
  OSCMessage msg("/climax");
  msg.add(123);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  climaxAudioSent = true;
}