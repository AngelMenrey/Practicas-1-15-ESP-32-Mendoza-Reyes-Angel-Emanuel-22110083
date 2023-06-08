// Librería para controlar los pines del ESP32
#include <Arduino.h>

// Pines de los LEDs
const int led1Pin = 32;
const int led2Pin = 33;
const int led3Pin = 26;

// Canal PWM para los LEDs
const int pwmChannel = 0;
// Frecuencia de PWM en Hz
const int pwmFrequency = 5000;
// Resolución de PWM (8 bits)
const int pwmResolution = 8;

// Tiempo de espera entre cada paso de fade
const int fadeDelay = 10;

void setup() {
  // Configurar los pines de los LEDs como salidas
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  
  // Configurar el LEDC para generar la señal PWM
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  // Asignar los pines a los canales PWM
  ledcAttachPin(led1Pin, pwmChannel);
  ledcAttachPin(led2Pin, pwmChannel);
  ledcAttachPin(led3Pin, pwmChannel);
}

void loop() {
  // Realizar el fade de los LEDs de 0 a 255 (máxima intensidad)
  for (int brightness = 0; brightness <= 255; brightness++) {
    ledcWrite(pwmChannel, brightness);
    delay(fadeDelay);
  }
  
  // Realizar el fade de los LEDs de 255 a 0 (apagado)
  for (int brightness = 255; brightness >= 0; brightness--) {
    ledcWrite(pwmChannel, brightness);
    delay(fadeDelay);
  }
}