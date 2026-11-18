# Sistema IoT de Monitoreo de Consumo Hídrico Residencial (TRL 5)

Prototipo funcional desarrollado en el marco del curso **Proyecto de Grado (202016907)** de la Universidad Nacional Abierta y a Distancia (UNAD) — Escuela de Ciencias Básicas, Tecnología e Ingeniería (ECBTI).

El sistema permite la medición, transmisión y visualización en tiempo real del caudal instantáneo y el volumen acumulado de agua en entornos residenciales, alineado con los Objetivos de Desarrollo Sostenible (**ODS 6**: Agua limpia y saneamiento; **ODS 7**: Energía asequible y no contaminante).

---

## Arquitectura del Sistema

El prototipo opera bajo una arquitectura IoT de tres capas:

1. **Capa de Percepción (Hardware):** Sensor de flujo de efecto Hall **YF-S201** acoplado a un microcontrolador **ESP32 DevKit V1 (30 pines)**.
2. **Capa de Red:** Conectividad inalámbrica mediante protocolo **Wi-Fi (IEEE 802.11 b/g/n)** integrada en el SoC ESP32.
3. **Capa de Aplicación (Cloud PaaS):** Plataforma **Blynk IoT**, encargada de recibir la telemetría mediante datastreams virtuales y desplegarla en paneles web y móviles en tiempo real.

---

## Esquema de Conexión (Pinout)

El sensor YF-S201 opera con alimentación de 5V DC y entrega pulsos digitales proporcionales al flujo de agua (calibrado mediante el factor estándar `7.5`).

| Cable del Sensor (YF-S201) | Función | Pin en ESP32 |
| :--- | :--- | :--- |
| **Rojo** | Alimentación (`+5V DC`) | `VIN` |
| **Negro** | Tierra común (`GND`) | `GND` |
| **Amarillo** | Señal de pulsos (Interrupción) | `GPIO 18` (`D18`) |

---

## Configuración en Blynk IoT (Datastreams)

Para replicar el tablero de control en Blynk Cloud, se utilizan los siguientes pines virtuales:

* **`V0` (Caudal Instantáneo):** Tipo `Double` | Unidades: `L/min` | Rango: `0` a `30`.
* **`V1` (Volumen Acumulado):** Tipo `Double` | Unidades: `Litros (L)` | Rango: `0` a `1000`.

---

## Requisitos de Software y Despliegue

1. **Entorno de desarrollo:** Arduino IDE (v2.x o superior) con el gestor de tarjetas *ESP32 by Espressif Systems* instalado.
2. **Librerías necesarias:**
   * `WiFi.h` (Nativa del core ESP32).
   * `BlynkSimpleEsp32.h` (Librería oficial de Blynk v1.3.2 o superior).
3. **Configuración de credenciales:** Antes de compilar y cargar el archivo `.ino` en la placa ESP32, edite las constantes superiores con los datos de su plantilla en Blynk y su red local:

```cpp
#define BLYNK_TEMPLATE_ID "TU_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Monitoreo Flujo de Agua"
#define BLYNK_AUTH_TOKEN "TU_AUTH_TOKEN"

char ssid[] = "TU_RED_WIFI";
char pass[] = "TU_CONTRASENA_WIFI";
```

---

## Autores

* Samuel Moisés Cuello Gamarra *(agregar nombres de los demás integrantes del grupo)*
* **Programa:** Ingeniería de Sistemas — UNAD (2026)
