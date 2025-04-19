#include <FastLED.h>
#include <ezButton.h>
#include <Stepper.h>
#include "WiFiS3.h"
#include <OSCMessage.h>

// EL IP DE ESTE ARDUINO ES 192.168.0.111

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
char ssid[] = "Router_Flora";
char pass[] = "Flora666";
// char ssid[] = "WIFIBAU";
// char pass[] = "bau934153474";

unsigned int localPort = 8881;

IPAddress outIp(192, 168, 1, 35);  // mariana wifi Flora_Router
// IPAddress outIp(192, 168, 0, 119);  // mariana innov
// IPAddress outIp(192, 168, 27, 100); // mariana wifi bau
// IPAddress outIp(192, 168, 0, 124);  // daniela wifi innov
const unsigned int outPort = 8000;

bool climaxAudioSent = false;

// *** PINES 5, 6, 8 ya estan cogidos para las LEDS ***

// Motor para flores giratorias
int stepsPerRevolution = 2048;  // steps per revolution

Stepper stepper(stepsPerRevolution, 9, 11, 12, 13);  // los 4 pines IN

// Motor para flores centrales
int motor1Pin1 = 9;
int motor1Pin2 = 12;
int motor1Velocidad = 11;    // PWM capable pin
int velocidadMotores = 255;  // entre 0 y 255

int pinBoton1 = 2;
int pinBoton2 = 3;
int pinBoton3 = 4;

int debounceTime = 50;  // En milisegundos

// Crear un ezButton object para cada uno de los limit switches
ezButton limitSwitch1(pinBoton1);
ezButton limitSwitch2(pinBoton2);
ezButton limitSwitch3(pinBoton3);

#define NUM_LEDS 5

// Definimos las tiras de led que tienen 1 solo led
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

// Estados de colores de leds
String led1State = "black";
String led2State = "black";
String led3State = "black";

// Define the colors
CRGB colors[] = { CRGB::Blue, CRGB::Purple, CRGB::Yellow, CRGB::Red, CRGB::Orange, CRGB::Pink };
const int numColors = sizeof(colors) / sizeof(colors[0]);

// Variables for current and target colors for each LED
CRGB targetColor1, targetColor2, targetColor3;
CRGB currentColor1, currentColor2, currentColor3;

// Fade durations in milliseconds for each LED
uint16_t fadeDuration1 = random(1000, 3000);
uint16_t fadeDuration2 = random(1000, 3000);
uint16_t fadeDuration3 = random(1000, 3000);

// Fade steps for each LED
uint16_t fadeStep1 = 0;
uint16_t fadeStep2 = 0;
uint16_t fadeStep3 = 0;

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
  FastLED.addLeds<NEOPIXEL, 5>(leds1, NUM_LEDS);  // pin 5
  FastLED.addLeds<NEOPIXEL, 6>(leds2, NUM_LEDS);  // pin 6
  FastLED.addLeds<NEOPIXEL, 8>(leds3, NUM_LEDS);  // pin 8

  FastLED.setBrightness(50);  // 0 a 255

  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    led1State = "black";

    leds2[i] = CRGB::Black;
    led2State = "black";

    leds3[i] = CRGB::Black;
    led3State = "black";
  }

  limitSwitch1.setDebounceTime(debounceTime);
  limitSwitch2.setDebounceTime(debounceTime);
  limitSwitch3.setDebounceTime(debounceTime);

  // stepper.setSpeed(5);  // rpm

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Velocidad, OUTPUT);
  analogWrite(motor1Velocidad, velocidadMotores);
}

void loop() {
  receiveMessage();

  limitSwitch1.loop();
  limitSwitch2.loop();
  limitSwitch3.loop();

  if (limitSwitch1.isPressed()) {
    sendAbejasAudioMessage();

    if (led1State == "black") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds1[i] = CRGB::Blue;
      }
      // led1State = "blue";
      led1State = "multicolor";
    } else if (led1State == "blue") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds1[i] = CRGB::Purple;
      }
      led1State = "purple";
    } else {
      currentColor1 = CRGB::Yellow;
      for (int i = 0; i < NUM_LEDS; i++) {
        leds1[i] = currentColor1;
      }
      led1State = "multicolor";
    }

    Serial.print("flor 1 se toco, ahora esta de color: ");
    Serial.println(led1State);
  }

  if (limitSwitch2.isPressed()) {
    sendAbejasAudioMessage();

    if (led2State == "black") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds2[i] = CRGB::Blue;
      }
      // led2State = "blue";
      led2State = "multicolor";
    } else if (led2State == "blue") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds2[i] = CRGB::Purple;
      }
      led2State = "purple";
    } else {
      currentColor2 = CRGB::Yellow;
      for (int i = 0; i < NUM_LEDS; i++) {
        leds2[i] = currentColor2;
      }
      led2State = "multicolor";
    }

    Serial.print("flor 2 se toco, ahora esta de color: ");
    Serial.println(led2State);
  }

  if (limitSwitch3.isPressed()) {
    // enviar senal OSC de audio
    sendAbejasAudioMessage();

    if (led3State == "black") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds3[i] = CRGB::Blue;
      }
      // led3State = "blue";
      led3State = "multicolor";
    } else if (led3State == "blue") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds3[i] = CRGB::Purple;
      }
      led3State = "purple";
    } else {
      currentColor3 = CRGB::Yellow;
      for (int i = 0; i < NUM_LEDS; i++) {
        leds3[i] = currentColor3;
      }
      led3State = "multicolor";
    }

    Serial.print("flor 3 se toco, ahora esta de color: ");
    Serial.println(led3State);
  }

  FastLED.show();

  // Cuando las 3 leds esten en su estado final ya "polinizado" prender el motor de las flores giratorias
  if (led1State == "multicolor" && led2State == "multicolor" && led3State == "multicolor") {
    Serial.println("Prender flores giratorias");

    // stepper.step(stepsPerRevolution);
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);

    if (!climaxAudioSent) sendClimaxAudioMessage();

    for (int i = 0; i < NUM_LEDS; i++) {
      CRGB color = colors[random(0, numColors)];
      leds1[i] = color;
      leds2[i] = color;
      leds3[i] = color;
    }

    // Show the updated colors on all LEDs
    FastLED.show();
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
  Serial.println("resetting abejas");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    led1State = "black";

    leds2[i] = CRGB::Black;
    led2State = "black";

    leds3[i] = CRGB::Black;
    led3State = "black";
  }

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  climaxAudioSent = false;
}
