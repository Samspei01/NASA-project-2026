C++
/*
 * Patient  Health Monitor
 *
 * I2C (SDA=21, SCL=22): BME280 @0x76, ADS1115 @0x48, MAX30102 @0x57
 * ADS1115 AIN0: AD8232 ECG   AIN1: NTC body temp
 * ECG_SDN -> D5, LO+ -> D18, LO- -> D19
 */
 
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <math.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MAX30105.h>
#include <spo2_algorithm.h>
#include "dashboard_page.h"
 
const char* WIFI_SSID = "****************";
const char* WIFI_PASSWORD = "***************";
 
static const int I2C_SDA_PIN = 21;
static const int I2C_SCL_PIN = 22;
static const int ECG_SDN_PIN = 5;
static const int LO_PLUS_PIN = 18;
static const int LO_MINUS_PIN = 19;
 
static const uint8_t ECG_CHANNEL = 0;
static const uint8_t THERMISTOR_CHANNEL = 1;
static const uint8_t ADS1115_I2C_ADDR = 0x48;
static const uint8_t BME280_I2C_ADDR = 0x76;
 
static const uint16_t SAMPLE_INTERVAL_MS = 8;
static const uint16_t SLOW_SENSOR_MS = 2000;
static const uint8_t ECG_QUEUE_SIZE = 28;
 
static const float SUPPLY_VOLTAGE = 3.3f;
static const float SERIES_RESISTOR_OHMS = 10000.0f;
static const float NTC_NOMINAL_OHMS = 10000.0f;
static const float NTC_NOMINAL_TEMP_C = 25.0f;
static const float NTC_BETA = 3950.0f;
 
static const long FINGER_IR_THRESHOLD = 50000;
static const int32_t SPO2_BUFFER_LENGTH = 100;
static const int32_t SPO2_SHIFT_SAMPLES = 25;
 
WebServer server(80);
Adafruit_ADS1115 ads;
Adafruit_BME280 bme;
MAX30105 particleSensor;
 
bool bmeOk = false;
bool maxOk = false;
 
unsigned long lastSampleMs = 0;
unsigned long lastSlowMs = 0;
unsigned long lastDebugMs = 0;
 
int lastEcgValue = 512;
int lastRawAdc = 0;
float lastVoltage = 0.0f;
bool lastLeadsOff = true;
int lastLoPlus = 0;
int lastLoMinus = 0;
 
int ecgQueue[ECG_QUEUE_SIZE];
volatile uint8_t ecgQWrite = 0;
volatile uint8_t ecgQRead = 0;
 
int ecgBpm = -1;
int32_t ecgBaseline = 512;
int ecgSignalLevel = 0;
bool ecgBeatArmed = true;
unsigned long lastRPeakMs = 0;

// HRV (RMSSD, ms) from the last <=20 R-R intervals; -1 until enough beats
int rrBuf[20];
uint8_t rrCount = 0;
uint8_t rrIdx = 0;
int hrvRmssd = -1;

float roomTempC = 0.0f;
float roomHumidity = 0.0f;
float bodyTempC = -999.0f;
int spo2Pct = -1;
bool fingerDetected = false;
 
uint32_t irBuffer[100];
uint32_t redBuffer[100];
int32_t spo2 = 0;
int8_t validSPO2 = 0;
int32_t maximHeartRate = 0;
int8_t validMaximHeartRate = 0;
 
byte sampleIndex = 0;
bool bufferFilled = false;
 
char jsonBuffer[384];
 
bool leadsOff() {
  lastLoPlus = digitalRead(LO_PLUS_PIN);
  lastLoMinus = digitalRead(LO_MINUS_PIN);
  return (lastLoPlus == HIGH) || (lastLoMinus == HIGH);
}
 
float readChannelVoltage(uint8_t channel) {
  int32_t sum = 0;
  for (uint8_t i = 0; i < 4; i++) {
    sum += ads.readADC_SingleEnded(channel);
    yield();
  }
  return ads.computeVolts((int16_t)(sum / 4));
}
 
float ntcResistanceFromVoltage(float voltage) {
  if (voltage <= 0.001f || voltage >= SUPPLY_VOLTAGE - 0.001f) {
    return NAN;
  }
  return SERIES_RESISTOR_OHMS * voltage / (SUPPLY_VOLTAGE - voltage);
}
 
float ntcResistanceToCelsius(float resistance) {
  if (isnan(resistance) || resistance <= 0.0f) {
    return NAN;
  }
  float steinhart = resistance / NTC_NOMINAL_OHMS;
  steinhart = log(steinhart);
  steinhart /= NTC_BETA;
  steinhart += 1.0f / (NTC_NOMINAL_TEMP_C + 273.15f);
  steinhart = 1.0f / steinhart;
  return steinhart - 273.15f;
}
 
float readBodyTemperatureC() {
  const float voltage = readChannelVoltage(THERMISTOR_CHANNEL);
  const float resistance = ntcResistanceFromVoltage(voltage);
  return ntcResistanceToCelsius(resistance);
}
 
int readEcgValue() {
  lastRawAdc = ads.readADC_SingleEnded(ECG_CHANNEL);
  lastVoltage = ads.computeVolts(lastRawAdc);
  return map(lastRawAdc, 0, 32767, 0, 1023);
}
 
void ecgQueueClear() {
  ecgQRead = 0;
  ecgQWrite = 0;
}
 
void ecgQueuePush(int value) {
  const uint8_t next = (uint8_t)((ecgQWrite + 1) % ECG_QUEUE_SIZE);
  if (next == ecgQRead) {
    ecgQRead = (uint8_t)((ecgQRead + 1) % ECG_QUEUE_SIZE);
  }
  ecgQueue[ecgQWrite] = value;
  ecgQWrite = next;
}
 
uint8_t ecgQueueDrain(int* out, uint8_t maxOut) {
  uint8_t count = 0;
  while (ecgQRead != ecgQWrite && count < maxOut) {
    out[count++] = ecgQueue[ecgQRead];
    ecgQRead = (uint8_t)((ecgQRead + 1) % ECG_QUEUE_SIZE);
  }
  return count;
}
 
void resetEcgBpm() {
  ecgBpm = -1;
  ecgBaseline = 512;
  ecgSignalLevel = 0;
  ecgBeatArmed = true;
  lastRPeakMs = 0;
  rrCount = 0;
  rrIdx = 0;
  hrvRmssd = -1;
  ecgQueueClear();
}

void pushRR(int rr) {
  // A >30% jump vs the previous interval is treated as noise/ectopic: restart the window
  if (rrCount > 0) {
    const int prev = rrBuf[(rrIdx + 19) % 20];
    if (abs(rr - prev) > (prev * 3) / 10) {
      rrCount = 0;
      hrvRmssd = -1;
    }
  }
  rrBuf[rrIdx] = rr;
  rrIdx = (uint8_t)((rrIdx + 1) % 20);
  if (rrCount < 20) rrCount++;

  if (rrCount >= 8) {
    const uint8_t start = (uint8_t)((rrIdx + 20 - rrCount) % 20);
    float sum = 0;
    for (uint8_t j = 1; j < rrCount; j++) {
      const float d = (float)(rrBuf[(start + j) % 20] - rrBuf[(start + j - 1) % 20]);
      sum += d * d;
    }
    hrvRmssd = (int)sqrtf(sum / (rrCount - 1));
  }
}

void updateEcgBpm(int sample) {
  ecgBaseline = (ecgBaseline * 995 + sample * 5) / 1000;
  const int hp = abs(sample - (int)ecgBaseline);
 
  ecgSignalLevel = (ecgSignalLevel * 127 + hp) / 128;
  const int threshold = max(18, (ecgSignalLevel * 3) / 2);
 
  if (hp > threshold && ecgBeatArmed) {
    const unsigned long now = millis();
    if (lastRPeakMs > 0) {
      const unsigned long interval = now - lastRPeakMs;
      if (interval >= 300 && interval <= 2000) {
        const int bpm = (int)(60000UL / interval);
        ecgBpm = (ecgBpm < 0) ? bpm : ((ecgBpm * 3) + bpm) / 4;
        pushRR((int)interval);
      }
    }
    lastRPeakMs = now;
    ecgBeatArmed = false;
  } else if (hp < threshold / 3) {
    ecgBeatArmed = true;
  }
}
 
void updateEcgSample() {
  const unsigned long now = millis();
  if (now - lastSampleMs < SAMPLE_INTERVAL_MS) {
    return;
  }
  lastSampleMs = now;
 
  lastLeadsOff = leadsOff();
  if (lastLeadsOff) {
    resetEcgBpm();
    lastEcgValue = 512;
    ecgQueuePush(512);
  } else {
    lastEcgValue = readEcgValue();
    ecgQueuePush(lastEcgValue);
    updateEcgBpm(lastEcgValue);
  }
}
 
void shiftBuffers() {
  for (byte i = SPO2_SHIFT_SAMPLES; i < SPO2_BUFFER_LENGTH; i++) {
    redBuffer[i - SPO2_SHIFT_SAMPLES] = redBuffer[i];
    irBuffer[i - SPO2_SHIFT_SAMPLES] = irBuffer[i];
  }
  sampleIndex = SPO2_BUFFER_LENGTH - SPO2_SHIFT_SAMPLES;
}
 
void calculateSpO2() {
  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, SPO2_BUFFER_LENGTH, redBuffer,
    &spo2, &validSPO2, &maximHeartRate, &validMaximHeartRate
  );
}
 
void updateSpO2Reading() {
  if (fingerDetected && validSPO2 && spo2 > 0 && spo2 <= 100) {
    spo2Pct = (int)spo2;
  } else {
    spo2Pct = -1;
  }
}
 
void updateMax30102() {
  if (!maxOk) {
    return;
  }
 
  particleSensor.check();
 
  while (particleSensor.available()) {
    const uint32_t irValue = particleSensor.getIR();
    const uint32_t redValue = particleSensor.getRed();
    particleSensor.nextSample();
 
    fingerDetected = (irValue >= FINGER_IR_THRESHOLD);
 
    if (!bufferFilled) {
      redBuffer[sampleIndex] = redValue;
      irBuffer[sampleIndex] = irValue;
      sampleIndex++;
      if (sampleIndex >= SPO2_BUFFER_LENGTH) {
        bufferFilled = true;
        calculateSpO2();
        sampleIndex = SPO2_BUFFER_LENGTH - SPO2_SHIFT_SAMPLES;
        updateSpO2Reading();
        server.handleClient();
      }
    } else {
      redBuffer[sampleIndex] = redValue;
      irBuffer[sampleIndex] = irValue;
      sampleIndex++;
      if (sampleIndex >= SPO2_BUFFER_LENGTH) {
        shiftBuffers();
        calculateSpO2();
        updateSpO2Reading();
        server.handleClient();
      }
    }
 
    yield();
    server.handleClient();
  }
}
 
void updateSlowSensors() {
  const unsigned long now = millis();
  if (now - lastSlowMs < SLOW_SENSOR_MS) {
    return;
  }
  lastSlowMs = now;
 
  if (bmeOk) {
    roomTempC = bme.readTemperature();
    roomHumidity = bme.readHumidity();
  }
 
  const float body = readBodyTemperatureC();
  bodyTempC = isnan(body) ? -999.0f : body;
 
  if (now - lastDebugMs >= 2000) {
    lastDebugMs = now;
    Serial.printf(
      "Room: %.1f C  Hum: %.1f%%  Body: %.1f C  SpO2: %d%% (valid=%d)  Finger: %s\n",
      roomTempC, roomHumidity, bodyTempC, spo2Pct, validSPO2, fingerDetected ? "yes" : "no"
    );
    Serial.printf(
      "ECG plot=%d  raw=%d  %.3fV  bpm=%d  leads=%s\n",
      lastEcgValue, lastRawAdc, lastVoltage, ecgBpm, lastLeadsOff ? "OFF" : "ON"
    );
  }
}
 
void handleRoot() {
  server.send_P(200, "text/html", DASHBOARD_PAGE);
}
 
void handleEcgApi() {
  int samples[ECG_QUEUE_SIZE];
  uint8_t count = ecgQueueDrain(samples, ECG_QUEUE_SIZE);
  if (count == 0) {
    samples[0] = lastEcgValue;
    count = 1;
  }
 
  char* p = jsonBuffer;
  int rem = (int)sizeof(jsonBuffer);
  int n = snprintf(p, rem, "{\"v\":[");
  p += n;
  rem -= n;
 
  for (uint8_t i = 0; i < count && rem > 12; i++) {
    if (i > 0) {
      *p++ = ',';
      rem--;
    }
    n = snprintf(p, rem, "%d", samples[i]);
    p += n;
    rem -= n;
  }
 
  snprintf(
    p, rem,
    "],\"lo\":%d,\"raw\":%d,\"mv\":%d,\"lp\":%d,\"lm\":%d,\"bpm\":%d}",
    lastLeadsOff ? 1 : 0,
    lastRawAdc,
    (int)(lastVoltage * 1000.0f),
    lastLoPlus,
    lastLoMinus,
    ecgBpm
  );
 
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json", jsonBuffer);
}
 
void handleVitalsApi() {
  snprintf(
    jsonBuffer, sizeof(jsonBuffer),
    "{\"roomT\":%.1f,\"hum\":%.1f,\"bodyT\":%.1f,\"spo2\":%d,\"spo2Valid\":%d,\"finger\":%d,\"bme\":%d,\"hrv\":%d}",
    roomTempC,
    roomHumidity,
    bodyTempC,
    spo2Pct,
    (validSPO2 && fingerDetected) ? 1 : 0,
    fingerDetected ? 1 : 0,
    bmeOk ? 1 : 0,
    hrvRmssd
  );
 
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json", jsonBuffer);
}
 
void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.print(F("Connecting to WiFi"));
  uint8_t attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(500);
    Serial.print('.');
    attempts++;
  }
  Serial.println();
 
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("WiFi failed."));
    return;
  }
 
  Serial.print(F("Open: http://"));
  Serial.println(WiFi.localIP());
}
 
void setup() {
  Serial.begin(115200);
  delay(500);
 
  pinMode(ECG_SDN_PIN, OUTPUT);
  digitalWrite(ECG_SDN_PIN, HIGH);
  pinMode(LO_PLUS_PIN, INPUT);
  pinMode(LO_MINUS_PIN, INPUT);
 
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
 
  if (!ads.begin(ADS1115_I2C_ADDR)) {
    Serial.println(F("ERROR: ADS1115 not found"));
    while (true) {
      delay(1000);
      yield();
    }
  }
  ads.setGain(GAIN_ONE);
  ads.setDataRate(RATE_ADS1115_128SPS);
  Serial.println(F("ADS1115 OK (ECG AIN0, NTC AIN1)"));
 
  bmeOk = bme.begin(BME280_I2C_ADDR);
  Serial.println(bmeOk ? F("BME280 OK") : F("BME280 not found"));
 
  maxOk = particleSensor.begin(Wire, I2C_SPEED_FAST);
  if (maxOk) {
    particleSensor.setup(60, 4, 2, 100, 411, 4096);
    particleSensor.setPulseAmplitudeGreen(0);
    Serial.println(F("MAX30102 OK (SparkFun SpO2 algorithm)"));
  } else {
    Serial.println(F("MAX30102 not found"));
  }
 
  setupWiFi();
 
  server.on("/", handleRoot);
  server.on("/api/ecg", handleEcgApi);
  server.on("/api/vitals", handleVitalsApi);
  server.begin();
 
  Serial.println(F("Patient  Health Monitor ready"));
}
 
void loop() {
  server.handleClient();
 
  if (WiFi.status() == WL_CONNECTED) {
    updateEcgSample();
    updateMax30102();
    updateSlowSensors();
    server.handleClient();
  }
 
  yield();
}
