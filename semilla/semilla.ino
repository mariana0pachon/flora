int pinSensorHumedad = A0;
int pinReleRio = 8;
// int pinMotorFlorSubeBaja = x;

void setup() {
  Serial.begin(9600);

  pinMode(pinSensorHumedad, INPUT);
  pinMode(pinReleRio, OUTPUT);
  // pinMode(pinMotorFlorSubeBaja, OUTPUT);
}

void loop() {
  if (analogRead(pinSensorHumedad) > 550) {

    // enviar senal OSC audio

    digitalWrite(pinReleRio, HIGH);

    // despues de un delay prender motor 1 flores suben y bajan

    // despues de un delay, enviar senal OSC mapping para la siguiente instruccion
  }
}
