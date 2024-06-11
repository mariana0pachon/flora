#include <FastLED.h>
#include <ezButton.h>
#include <Stepper.h>
#include "WiFiS3.h"
#include <OSCMessage.h>

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
char ssid[] = "Innovacion";
char pass[] = "Innovacion24";
// char ssid[] = "WIFIBAU";
// char pass[] = "bau934153474";

unsigned int localPort = 8881;

// IPAddress outIp(192, 168, 0, 106); // mariana innov
// IPAddress outIp(192, 168, 27, 100); // mariana wifi bau
IPAddress outIp(192, 168, 0, 124);  // daniela wifi innov
const unsigned int outPort = 8000;

bool climaxAudioSent = false;

// *** PINES 5, 6, 8 ya estan cogidos para las LEDS ***

// Motor para flores giratorias
int stepsPerRevolution = 2048;  // steps per revolution

Stepper stepper(stepsPerRevolution, 9, 11, 12, 13);  // los 4 pines IN

// Motor para flores centrales
int motor1Pin1 = 9;
int motor1Pin2 = 12;
int motor1Velocidad = 11;   // PWM capable pin
int velocidadMotores = 90;  // entre 0 y 255

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
  FastLED.addLeds<NEOPIXEL, 5>(leds1, 1);  // pin 5
  FastLED.addLeds<NEOPIXEL, 6>(leds2, 1);  // pin 6
  FastLED.addLeds<NEOPIXEL, 8>(leds3, 1);  // pin 8

  FastLED.setBrightness(50);  // 0 a 255

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
  limitSwitch1.loop();
  limitSwitch2.loop();
  limitSwitch3.loop();

  if (limitSwitch1.isPressed()) {
    sendAbejasAudioMessage();

    if (led1State == "black") {
      leds1[0] = CRGB::Blue;
      led1State = "blue";
    } else if (led1State == "blue") {
      leds1[0] = CRGB::Purple;
      led1State = "purple";
    } else {
      currentColor1 = CRGB::Yellow;
      leds1[0] = currentColor1;
      led1State = "multicolor";
    }

    Serial.print("flor 1 se toco, ahora esta de color: ");
    Serial.println(led1State);
  }

  if (limitSwitch2.isPressed()) {
    sendAbejasAudioMessage();

    if (led2State == "black") {
      leds2[0] = CRGB::Blue;
      led2State = "blue";
    } else if (led2State == "blue") {
      leds2[0] = CRGB::Purple;
      led2State = "purple";
    } else {
      currentColor2 = CRGB::Yellow;
      leds2[0] = currentColor2;
      led2State = "multicolor";
    }

    Serial.print("flor 2 se toco, ahora esta de color: ");
    Serial.println(led2State);
  }

  if (limitSwitch3.isPressed()) {
    // enviar senal OSC de audio
    sendAbejasAudioMessage();

    if (led3State == "black") {
      leds3[0] = CRGB::Blue;
      led3State = "blue";
    } else if (led3State == "blue") {
      leds3[0] = CRGB::Purple;
      led3State = "purple";
    } else {
      currentColor3 = CRGB::Yellow;
      leds3[0] = currentColor3;
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


    // Handle fading effect for LED 1
    EVERY_N_MILLISECONDS(fadeDuration1 / 255) {
      fadeStep1++;
      if (fadeStep1 > 255) {
        fadeStep1 = 0;
        targetColor1 = colors[random(0, numColors)];
        fadeDuration1 = random(1000, 3000);
      }
      currentColor1 = blend(currentColor1, targetColor1, fadeStep1);
      leds1[0] = currentColor1;
    }

    // Handle fading effect for LED 2
    EVERY_N_MILLISECONDS(fadeDuration2 / 255) {
      fadeStep2++;
      if (fadeStep2 > 255) {
        fadeStep2 = 0;
        targetColor2 = colors[random(0, numColors)];
        fadeDuration2 = random(1000, 3000);
      }
      currentColor2 = blend(currentColor2, targetColor2, fadeStep2);
      leds2[0] = currentColor2;
    }

    // Handle fading effect for LED 3
    EVERY_N_MILLISECONDS(fadeDuration3 / 255) {
      fadeStep3++;
      if (fadeStep3 > 255) {
        fadeStep3 = 0;
        targetColor3 = colors[random(0, numColors)];
        fadeDuration3 = random(1000, 3000);
      }
      currentColor3 = blend(currentColor3, targetColor3, fadeStep3);
      leds3[0] = currentColor3;
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

  leds1[0] = CRGB::Black;
  led1State = "black";

  leds2[0] = CRGB::Black;
  led2State = "black";

  leds3[0] = CRGB::Black;
  ed3State = "black";

  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
}