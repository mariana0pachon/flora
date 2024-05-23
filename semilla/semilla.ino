int pinSensorHumedad = A0;
int pinReleRio = 8;
int motorPin1 = 4;
int motorPin2 = 2;

void setup() {
  Serial.begin(9600);

  pinMode(pinSensorHumedad, INPUT);
  pinMode(pinReleRio, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  if (analogRead(pinSensorHumedad) > 550) {
    Serial.println("se planto la semilla");

    // enviar senal OSC audio

    digitalWrite(pinReleRio, HIGH);

    delay(1000);  // Ver si se necesita mas delay
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

    // despues de un delay, enviar senal OSC mapping para la siguiente instruccion
  }
}
