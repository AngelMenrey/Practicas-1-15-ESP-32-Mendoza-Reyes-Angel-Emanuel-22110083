
#include "esp_now.h"
#include "WiFi.h"
int valor_ent;
float valor_dec;
bool valor_bol = true;
uint8_t broadcast[] = {0xCC, 0xDB, 0xA7, 0x62, 0x97, 0x5C};

typedef struct mensaje{
  char a[32];
  int b;
  float c;
  bool d;
}mensaje;

mensaje Datos;
esp_now_peer_info_t peerInfo;
void EnvioDatos(const uint8_t *mac_dir, esp_now_send_status_t estado){
  Serial.print("\r\nEstado del último paquete enviado:");
  Serial.println(estado == ESP_NOW_SEND_SUCCESS ? "Envío correcto" : "Envío fallido");
}

void setup() {
  Serial.begin(9600); 
  WiFi.mode(WIFI_MODE_STA);
  if(esp_now_init() != ESP_OK){
    Serial.println("Error al iniciar ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(EnvioDatos);

  memcpy(peerInfo.peer_addr, broadcast, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if(esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Error al agregar peer.");
    return;
  }
}

void loop() {
  valor_ent = random(1, 20);

  valor_dec = 1.3 * valor_ent;

  valor_bol =! valor_bol;

  strcpy(Datos.a, "Bienvenido al taller.");
  Datos.b = valor_ent;
  Datos.c = valor_dec;
  Datos.d = valor_bol;

  esp_err_t resultado = esp_now_send(broadcast, (uint8_t *) &Datos, sizeof(Datos));

  if(resultado == ESP_OK){
    Serial.println("Enviado con éxito.");
  }
  else{
    Serial.println("Fallo al enviar.");
  }
  delay(3000);
}
