#include <FastLED.h>
#include <ezButton.h>

// *** PINES 2, 3, 4 ya estan cogidos para las LEDS ***

// Motor para flores giratorias
int motorPin1 = 10;
int motorPin2 = 11;

int pinBoton1 = 7;
int pinBoton2 = 8;
int pinBoton3 = 9;

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
  // Inicializamos los pines de los LEDs como salidas
  FastLED.addLeds<NEOPIXEL, 2>(leds1, 1);  // pin 2
  FastLED.addLeds<NEOPIXEL, 3>(leds2, 1);  // pin 3
  FastLED.addLeds<NEOPIXEL, 4>(leds3, 1);  // pin 4

  limitSwitch1.setDebounceTime(debounceTime);
  limitSwitch2.setDebounceTime(debounceTime);
  limitSwitch3.setDebounceTime(debounceTime);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  limitSwitch1.loop();
  limitSwitch2.loop();
  limitSwitch3.loop();

  if (limitSwitch1.isPressed()) {
    Serial.print("flor 1 se toco, ahora esta de color: ");
    Serial.println(led1State);

    // enviar senal OSC de audio

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
  }

  if (limitSwitch2.isPressed()) {
    Serial.print("flor 2 se toco, ahora esta de color: ");
    Serial.println(led2State);

    // enviar senal OSC de audio

    if (led2State == "black") {
      leds2[0] = CRGB::White;
      led1State = "white";
    } else if (led2State == "white") {
      leds2[0] = CRGB::Red;
      led2State = "red";
    } else {
      leds2[0] = CRGB::Black;
      led2State = "black";
    }
  }

  if (limitSwitch3.isPressed()) {
    Serial.print("flor 3 se toco, ahora esta de color: ");
    Serial.println(led3State);

    // enviar senal OSC de audio

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
  }

  FastLED.show();

  // Cuando las 3 leds esten en su estado final ya "polinizado" prender el motor de las flores giratorias
  if (led1State == "red" && led2State == "red" && led3State == "red") {
    // enviar senal OSC para el climax del audio

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
}