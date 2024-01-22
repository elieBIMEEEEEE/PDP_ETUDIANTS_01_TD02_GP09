#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

void takeReading() {
    sensors_event_t temp_event;
    dht.temperature().getEvent(&temp_event);
    if (!isnan(temp_event.temperature)) {
        Serial.print(F("Température: "));
        Serial.print(temp_event.temperature);
        Serial.println(F("°C"));
    } else {
        Serial.println(F("Error reading temperature!"));
    }

    sensors_event_t humidity_event;
    dht.humidity().getEvent(&humidity_event);
    
    if (!isnan(humidity_event.relative_humidity)) {
        Serial.print(F("Humiditée: "));
        Serial.print(humidity_event.relative_humidity);
        Serial.println(F("%"));
    } else {
        Serial.println(F("Error reading humidity!"));
    }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  
  esp_sleep_enable_timer_wakeup(5000000ULL);
  takeReading();
  
  Serial.flush();
  delay(20);
  esp_deep_sleep_start();
}

void loop() {
  // Vide car le deep sleep est géré dans setup
}

