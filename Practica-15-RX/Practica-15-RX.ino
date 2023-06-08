
#include <WiFi.h>
#include <esp_now.h>

typedef struct mensaje{
  char a[32];
  int b;
  float c;
  bool d;
}mensaje;

mensaje Datos;

void ReciboDatos(const uint8_t *mac, const uint8_t *entrante, int len){
  memcpy(&Datos, entrante, sizeof(Datos));
  Serial.print("Dato recibido: ");
  Serial.println(len);
  Serial.print("Valor de tipo caracter: ");
  Serial.println(Datos.a);
  Serial.print("Valor de tipo entero: ");
  Serial.println(Datos.b);
  Serial.print("Valor de tipo flotante: ");
  Serial.println(Datos.c);
  Serial.print("Valor de tipo booleano: ");
  Serial.println(Datos.d);
  Serial.println();
}

void setup() {
  Serial.begin(9600); 
    WiFi.mode(WIFI_STA); 
 
  if(esp_now_init() != ESP_OK){
    Serial.println("Error al iniciar ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(ReciboDatos);  
}

void loop() {
}
