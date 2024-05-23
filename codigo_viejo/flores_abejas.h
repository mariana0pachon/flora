// #include <FastLED.h>

// #include "especie.h"

// #ifndef flores_abejas_h
// #define flores_abejas_h

// class FloresAbejas : public Especie {
//   CRGB leds1[1];
//   CRGB leds2[1];
//   CRGB leds3[1];

//   // Estados de leds
//   int piezo1State = 0;
//   int prevPiezo1State = 0;
//   String led1State = "black";

//   int piezo2State = 0;
//   int prevPiezo2State = 0;
//   String led2State = "black";

//   int piezo3State = 0;
//   int prevPiezo3State = 0;
//   String led3State = "black";

//   int threshold = 80;

// public:
//   void setup() {
//     // Inicializamos los pines de los LEDs como salidas
//     FastLED.addLeds<NEOPIXEL, 0>(leds1, 1);
//     FastLED.addLeds<NEOPIXEL, 1>(leds2, 1);
//     FastLED.addLeds<NEOPIXEL, 2>(leds3, 1);

//     // Configuramos los pines de los sensores piezoeléctricos como entradas
//     pinMode(piezoPin1Abejas, INPUT);
//     pinMode(piezoPin2Abejas, INPUT);
//     pinMode(piezoPin3Abejas, INPUT);
//   }

//   void desbloquear(int nuevoNivel) {
//     piezo1State = analogRead(piezoPin1Abejas);
//     if (piezo1State > threshold && prevPiezo1State < 10) {
//       if (led1State == "black") {
//         leds1[0] = CRGB::White;
//         led1State = "white";
//       } else if (led1State == "white") {
//         leds1[0] = CRGB::Red;
//         led1State = "red";
//       } else {
//         leds1[0] = CRGB::Black;
//         led1State = "black";
//       }
//     }
//     prevPiezo1State = piezo1State;

//     Serial.println(analogRead(piezoPin2Abejas));

//     piezo2State = analogRead(piezoPin2Abejas);
//     if (piezo2State > threshold && prevPiezo2State < 10) {
//       if (led2State == "black") {
//         leds2[0] = CRGB::White;
//         led1State = "white";
//       } else if (led2State == "white") {
//         leds2[0] = CRGB::Red;
//         led2State = "red";
//       } else {
//         leds2[0] = CRGB::Black;
//         led2State = "black";
//       }
//     }
//     prevPiezo2State = piezo2State;

//     piezo3State = analogRead(piezoPin3Abejas);
//     if (piezo3State > threshold && prevPiezo3State < 10) {
//       if (led3State == "black") {
//         leds3[0] = CRGB::White;
//         led3State = "white";
//       } else if (led3State == "white") {
//         leds3[0] = CRGB::Red;
//         led3State = "red";
//       } else {
//         leds3[0] = CRGB::Black;
//         led3State = "black";
//       }
//     }
//     prevPiezo3State = piezo3State;

//     FastLED.show();

//     // Esperamos un breve periodo de tiempo antes de volver a leer los sensores
//     delay(100);
//   }
// };

// #endif
