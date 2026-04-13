#include <DHT.h>
#include "plant_chip.h"
#include <WiFi.h>
#include "mqtt_client.h"

// -------------------- WIFI + MQTT --------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

#define MQTT_BROKER "mqtt://test.mosquitto.org"
#define MQTT_TOPIC "eece5155/tdavis/plant"

esp_mqtt_client_handle_t client;

// -------------------- PINS --------------------
#define SOIL_PIN 34
#define LDR_PIN 35
#define DHT_PIN 4
#define DHT_TYPE DHT22

// -------------------- ALERT THRESHOLD --------------------
#define HEALTH_THRESHOLD 40

DHT dht(DHT_PIN, DHT_TYPE);
PlantChip plant;

// -------------------- VARIABLES --------------------
float humidity = 60;
float previousSoil = 60;

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  // WiFi connect
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // MQTT setup
  esp_mqtt_client_config_t cfg = {};
  cfg.broker.address.uri = MQTT_BROKER;

  client = esp_mqtt_client_init(&cfg);
  esp_mqtt_client_start(client);

  Serial.println("MQTT client started");
}

// -------------------- LOOP --------------------
void loop() {

  // ---------- TIMESTAMP ----------
  unsigned long timestamp = millis();

  // ---------- RAW READINGS ----------
  int soilRaw = analogRead(SOIL_PIN);
  int potSoil = map(soilRaw, 0, 4095, 0, 100);

  int lightRaw = analogRead(LDR_PIN);
  int lightPercent = map(lightRaw, 0, 4095, 0, 100);

  // simulate humidity
  humidity += random(-3, 2);
  if (humidity < 40) humidity = 40;
  if (humidity > 80) humidity = 80;

  // ---------- CHIP UPDATE ----------
  plant.update(potSoil, humidity, lightPercent);

  float soil = plant.getSoil();
  float stress = plant.getStress();
  float health = plant.getHealth();

  // ---------- ALERT LOGIC ----------
  bool healthAlert = (health < HEALTH_THRESHOLD);

  // ---------- JSON PAYLOAD ----------
  String payload = "{";
  payload += "\"ts\":" + String(timestamp) + ",";
  payload += "\"soil\":" + String(soil) + ",";
  payload += "\"humidity\":" + String(humidity) + ",";
  payload += "\"light\":" + String(lightPercent) + ",";
  payload += "\"stress\":" + String(stress) + ",";
  payload += "\"health\":" + String(health) + ",";
  payload += "\"alert\":" + String(healthAlert ? 1 : 0);
  payload += "}";

  // ---------- MQTT PUBLISH ----------
  esp_mqtt_client_publish(client, MQTT_TOPIC, payload.c_str(), 0, 1, 0);

  Serial.print("[MQTT PUBLISH] ");
  Serial.println(payload);

  // ---------- EVENTS ----------
  bool watered = (soil > previousSoil + 10);
  bool humidifierFlag = (soil < 30 && humidity < 45);

  // ---------- OUTPUT ----------
  Serial.print("Soil: ");
  Serial.print(soil);
  Serial.print("% | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Light: ");
  Serial.print(lightPercent);
  Serial.print("% | Stress: ");
  Serial.print(stress);
  Serial.print(" | Health: ");
  Serial.print(health);

  if (watered) Serial.print(" | Water Event!");
  if (humidifierFlag) Serial.print(" | Humidifier ON");
  if (healthAlert) Serial.print(" | ALERT: Low Plant Health!");

  Serial.println();

  previousSoil = soil;

  delay(2000);
}