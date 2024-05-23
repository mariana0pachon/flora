#include <FastLED.h>

// Definimos los pines de los sensores piezoeléctricos
const int piezoPin1 = A0;
const int piezoPin2 = A1;
const int piezoPin3 = A2;

// Definimos las tiras de led que tienen 1 solo led
CRGB leds1[1];
CRGB leds2[1];
CRGB leds3[1];

// Estados de leds
int piezo1State = 0;
int prevPiezo1State = 0;
String led1State = "black";

int piezo2State = 0;
int prevPiezo2State = 0;
String led2State = "black";

int piezo3State = 0;
int prevPiezo3State = 0;
String led3State = "black";

int threshold = 80;

void setup() {
  // Inicializamos los pines de los LEDs como salidas
  FastLED.addLeds<NEOPIXEL, 2>(leds1, 1);
  FastLED.addLeds<NEOPIXEL, 3>(leds2, 1);
  FastLED.addLeds<NEOPIXEL, 4>(leds3, 1);

  // Configuramos los pines de los sensores piezoeléctricos como entradas
  pinMode(piezoPin1, INPUT);
  pinMode(piezoPin2, INPUT);
  pinMode(piezoPin3, INPUT);
}

void loop() {
  piezo1State = analogRead(piezoPin1);
  if (piezo1State > threshold && prevPiezo1State < 10) {
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
  prevPiezo1State = piezo1State;

  piezo2State = analogRead(piezoPin2);
  if (piezo2State > threshold && prevPiezo2State < 10) {
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
  prevPiezo2State = piezo2State;

  piezo3State = analogRead(piezoPin3);
  if (piezo3State > threshold && prevPiezo3State < 10) {
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
  prevPiezo3State = piezo3State;

  FastLED.show();

  // Esperamos un breve periodo de tiempo antes de volver a leer los sensores
  delay(100);
}