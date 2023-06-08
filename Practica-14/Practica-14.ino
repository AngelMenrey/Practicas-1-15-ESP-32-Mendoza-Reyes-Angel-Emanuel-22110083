//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
/*const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "ESP32-BT-Slave";*/

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/*#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif*/

BluetoothSerial SerialBT;

const int ledPin = 5;

String message = "";
char incomingChar;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  SerialBT.begin("Angel"); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n");
  
}

void loop() {
  if (SerialBT.available()) {
    //SerialBT.write(Serial.read());
    char incomingChar = SerialBT.read();
    if(incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);
  }

  if (message == "led_on"){
    digitalWrite(ledPin, HIGH);
    //Serial.write(SerialBT.read());
  }
  else if(message == "led_off"){
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}
