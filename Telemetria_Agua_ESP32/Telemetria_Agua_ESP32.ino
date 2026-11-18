// 1. CREDENCIALES DE TU DISPOSITIVO EN BLYNK CONSOLE
#define BLYNK_TEMPLATE_ID "Tu  Template"
#define BLYNK_TEMPLATE_NAME "Sensor de Flujo"
#define BLYNK_AUTH_TOKEN "Tu Token"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// 2. CREDENCIALES WI-FI (BANDA 2.4 GHz)
char ssid[] = "Nombre Wifi";
char pass[] = "Contraseña Wifi";

// 3. MAPEO DE HARDWARE Y VARIABLES
const byte SENSOR_PIN = 18;
volatile unsigned long pulseCount = 0;

float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
float totalLitres = 0.0;

// Factor nominal del sensor YF-S201: F = 7.5 * Q (L/min)
const float calibrationFactor = 7.5;

BlynkTimer timer;

// Interrupción en RAM
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

// Función periódica cada 1 segundo (no bloqueante)
void sendTelemetry() {
  unsigned long currentPulses;

  // Lectura atómica de la variable volátil
  noInterrupts();
  currentPulses = pulseCount;
  pulseCount = 0;
  interrupts();

  // Caudal instantáneo en L/min
  flowRate = (currentPulses / calibrationFactor);

  // Volumen acumulado en el intervalo
  flowMilliLitres = (flowRate / 60.0) * 1000.0;
  totalMilliLitres += flowMilliLitres;
  totalLitres = totalMilliLitres / 1000.0;

  // Envío a Blynk
  Blynk.virtualWrite(V0, flowRate);
  Blynk.virtualWrite(V1, totalLitres);

  // Depuración por consola serial
  Serial.print("Caudal: ");
  Serial.print(flowRate, 2);
  Serial.print(" L/min | Acumulado: ");
  Serial.print(totalLitres, 3);
  Serial.println(" L");
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);
  timer.setInterval(1000L, sendTelemetry);
}

void loop() {
  Blynk.run();
  timer.run();
}