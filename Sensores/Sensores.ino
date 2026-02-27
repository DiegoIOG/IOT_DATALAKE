#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
#define BUTTONPIN 2

#define REDPIN 9
#define GREENPIN 10

DHT dht(DHTPIN, DHTTYPE);

bool systemActive = true;
bool lastState = HIGH;

unsigned long lastReadTime = 0;
unsigned long interval = 3000;

void setGreen() {
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 255);
}

void setRed() {
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 0);
}

void sendStatusOnly() {
  Serial.print("{\"device_id\":\"sensor_01\",\"status\":\"OFF\"}");
  Serial.println();
}

void sendSensorData(float t, float h) {
  Serial.print("{\"device_id\":\"sensor_01\",\"status\":\"ON\",\"temp\":");
  Serial.print(t);
  Serial.print(",\"hum\":");
  Serial.print(h);
  Serial.println("}");
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);

  dht.begin();

  setGreen();
}

void loop() {

  bool currentState = digitalRead(BUTTONPIN);

  // Detectar presión
  if (lastState == HIGH && currentState == LOW) {

    systemActive = !systemActive;

    if (systemActive) {
      setGreen();
    } else {
      setRed();
      sendStatusOnly();  // Enviar evento OFF
    }
  }

  lastState = currentState;

  if (systemActive) {

    unsigned long currentMillis = millis();

    if (currentMillis - lastReadTime >= interval) {
      lastReadTime = currentMillis;

      float h = dht.readHumidity();
      float t = dht.readTemperature();

      if (!isnan(h) && !isnan(t)) {
        sendSensorData(t, h);
      }
    }
  }
}