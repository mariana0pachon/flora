#include "WiFiS3.h"
#include <OSCMessage.h>

WiFiUDP Udp;
int update_rate = 16;  // Update rate for OSC data reception
// char ssid[] = "Innovacion";
// char pass[] = "Innovacion24";
char ssid[] = "WIFIBAU";
char pass[] = "bau934153474";

unsigned int localPort = 8881;

// IPAddress outIp(192, 168, 0, 106);
IPAddress outIp(192, 168, 27, 100);
const unsigned int outPort = 8000;

#define LUZ_2_PIN A1

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

  pinMode(LUZ_2_PIN, OUTPUT);
}

void loop() {
  // delay(5000);
  // Serial.println();
  // sendAudioMessage();

  // Serial.println("in loop");
  // Serial.println(analogRead(pinSensorHumedad));

  if (analogRead(pinSensorHumedad) > 0) {
    semillaPlantada = true;
  }

  if (semillaPlantada) {
    Serial.println("se planto la semilla");

    if (!audioSent) sendAudioMessage();

    digitalWrite(pinReleRio, HIGH);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
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
