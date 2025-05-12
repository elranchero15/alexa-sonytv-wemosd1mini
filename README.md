
# Control de TV Sony por Alexa (sin skill)

Este proyecto permite controlar una televisión Sony Bravia usando un microcontrolador **Wemos D1 Mini (ESP8266)**, un **LED infrarrojo** y comandos de voz por **Alexa**, sin necesidad de skills ni servicios externos.

> Diseñado especialmente para quienes han tenido problemas con la integración oficial de Sony Bravia y Alexa, o para quienes ya no pueden usar la skill del fabricante. Esta solución funciona sin depender de servicios externos ni de conectividad en la nube.

---

## 🔧 Características

- Enciende o apaga la TV
- Silencia o reactiva el sonido
- Pausa o reanuda la reproducción
- Compatible con Alexa usando **FauxmoESP** (emulación de dispositivos WeMo)
- Configuración WiFi fácil mediante portal cautivo (WiFiManager)

---

## 📚 Requisitos

- 1x Wemos D1 Mini (ESP8266)
- 1x LED IR + resistencia de 100Ω (opcionalmente con transistor NPN para mejor alcance)
- Cables y alimentación USB

---

## ⚖️ Librerías necesarias

Instalables desde el Gestor de Librerías de Arduino IDE:
- `WiFiManager` de tzapu
- `FauxmoESP`
- `IRremoteESP8266` (**solo usada para enviar**)

---

## 🏠 Conexiones

| Elemento      | Pin en Wemos D1 Mini |
|---------------|----------------------|
| LED IR (+)    | D2 (GPIO4)           |
| LED IR (-)    | GND (vía resistencia) |

---

## 💻 Subir el Sketch

1. Conecta el Wemos al PC.
2. Abre el sketch `tv_control_alexa.ino`.
3. Selecciona la placa `LOLIN(WEMOS) D1 R2 & mini` y el puerto correcto.
4. Sube el código.

---

## 🔑 Primera configuración WiFi

1. Al no encontrar WiFi guardada, el dispositivo creará una red llamada `Control Televisión Sony`.
2. Conéctate desde tu celular.
3. Se abrirá una página para ingresar los datos de tu red WiFi.
4. Una vez conectado, el dispositivo quedará listo.

---

## 🎧 Comandos de voz para Alexa

Luego de decir "**Alexa, busca dispositivos**" y encontrarlos, puedes usar:

- "Alexa, enciende **tv**"
- "Alexa, apaga **tv**"
- "Alexa, enciende **mute en la tele**"
- "Alexa, apaga **mute en la tele**"
- "Alexa, enciende **pausa en la tele**"
- "Alexa, enciende **reproduce en la tele**"

*("pausa" y "reproduce" usan el mismo código IR toggle)*

---

## 🌐 Autor

Proyecto por elranchero15.

Puedes reutilizar o adaptar este código para otros dispositivos IR controlables por Alexa sin skill.

---

📍¡Si lo mejoras o lo adaptas a otra marca, ¡no dudes en compartirlo también!
