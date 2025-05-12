#include <ESP8266WiFi.h>     // Librería para conexión WiFi en ESP8266
#include <WiFiManager.h>     // Librería para configurar WiFi desde el navegador
#include <fauxmoESP.h>       // Librería para emular dispositivos controlados por Alexa
#include <IRsend.h>          // Librería para enviar señales infrarrojas

// Definir el pin donde está conectado el LED infrarrojo (D2 en Wemos D1 Mini = GPIO4)
const uint8_t irPin = D2;
IRsend irsend(irPin); // Crear instancia del emisor IR

// Crear instancia de Fauxmo para simular dispositivos con Alexa
fauxmoESP fauxmo;

void setup() {
  pinMode(irPin, OUTPUT);    // Configurar el pin IR como salida
  irsend.begin();            // Iniciar el emisor IR

  // Iniciar WiFiManager: crea un AP si no hay WiFi conocida
  WiFiManager wm;
  wm.setTimeout(180);  // Tiempo de espera en segundos para configurar WiFi
  if (!wm.autoConnect("Control Televisión Sony")) {
    ESP.restart();     // Si no se configura a tiempo, reinicia el ESP
  }

  // Configurar Fauxmo para emular dispositivos Alexa
  fauxmo.createServer(true); // Habilita servidor SSDP para detección
  fauxmo.setPort(80);        // Puerto HTTP (por defecto)
  fauxmo.enable(true);       // Activar Fauxmo

  // Añadir dispositivos que Alexa puede controlar
  fauxmo.addDevice("tv");                    // Enciende o apaga la televisión
  fauxmo.addDevice("mute en la tele");       // Silencia o reactiva el sonido
  fauxmo.addDevice("pausa en la tele");      // Pausa o reanuda reproducción
  fauxmo.addDevice("reproducción en la tele");  // Reproduce o pausa (mismo código que el anterior)

  // Definir las acciones que se ejecutan al recibir comandos de Alexa
  fauxmo.onSetState([](unsigned char device_id, const char* device_name, bool state, unsigned char value) {
    // Ejecutar siempre que el dispositivo reciba un cambio de estado (on/off)
    if (strcmp(device_name, "tv") == 0) {
      irsend.sendSony(0xA90, 12); // Enviar código Power Toggle (enciende/apaga)
    } else if (strcmp(device_name, "mute en la tele") == 0) {
      irsend.sendSony(0x290, 12); // Enviar código de Mute
    } else if (strcmp(device_name, "pausa en la tele") == 0) {
      irsend.sendSony(0xA0, 12);  // Enviar código Play/Pause
    } else if (strcmp(device_name, "reproducción en la tele") == 0) {
      irsend.sendSony(0xA0, 12);  // Mismo código Play/Pause
    }
  });
}

void loop() {
  fauxmo.handle(); // Mantener Fauxmo funcionando (manejo de Alexa)
}

void loop() {
  fauxmo.handle();
}
