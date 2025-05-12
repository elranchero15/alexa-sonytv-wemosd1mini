#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <fauxmoESP.h>
#include <IRsend.h>

// Pin IR (D2 = GPIO4 en Wemos D1 Mini)
const uint8_t irPin = D2;
IRsend irsend(irPin);

// Alexa
fauxmoESP fauxmo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(irPin, OUTPUT);
  irsend.begin();

  // WiFiManager
  WiFiManager wm;
  wm.setTimeout(180);
  if (!wm.autoConnect("Control Televisión Sony")) {
    Serial.println("⏱️ Sin WiFi. Reiniciando...");
    ESP.restart();
  }

  Serial.println("✅ Conectado a WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Fauxmo
  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);

  // Dispositivos: encendido, mute y reproducción
  fauxmo.addDevice("tv");
  fauxmo.addDevice("mute en la tele");
  fauxmo.addDevice("pausa en la tele");
  fauxmo.addDevice("reproduce en la tele");

  // Acción al recibir comando de Alexa
  fauxmo.onSetState([](unsigned char device_id, const char* device_name, bool state, unsigned char value) {
    Serial.printf("🧠 Alexa dijo: %s = %s\n", device_name, state ? "ON" : "OFF");

    if (strcmp(device_name, "tv") == 0) {
      irsend.sendSony(0xA90, 12); // Power toggle
    } else if (strcmp(device_name, "mute en la tele") == 0) {
      irsend.sendSony(0x290, 12); // Mute toggle
    } else if (strcmp(device_name, "pausa en la tele") == 0) {
      irsend.sendSony(0xA0, 12);  // Play/Pause toggle
    } else if (strcmp(device_name, "reproduce en la tele") == 0) {
      irsend.sendSony(0xA0, 12);  // Play/Pause toggle
    }
  });
}

void loop() {
  fauxmo.handle();
}
