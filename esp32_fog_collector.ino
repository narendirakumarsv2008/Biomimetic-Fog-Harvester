#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// --- Pin Definitions ---
#define DHTPIN 4
#define WATER_SENSOR_PIN 34
#define FAN_PIN 26

// --- Object Initialization ---
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Variables for Timing and Display ---
unsigned long previousOledMillis = 0;
const long oledInterval = 2000; // Refresh display every 2 seconds

float totalCollectedML = 0.0;
float previousWaterLevelRaw = 0;
// Calibration factor: Adjust this after testing actual volumes in your jar
const float ADC_TO_ML_FACTOR = 0.05; 

void setup() {
  Serial.begin(115200);

  // Initialize Fan Pin
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, HIGH); // Turn on optional fan

  // Initialize DHT
  dht.begin();

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("System Starting...");
  display.display();

  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Display Update (Every 2 seconds) ---
  if (currentMillis - previousOledMillis >= oledInterval) {
    previousOledMillis = currentMillis;

    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int wLevelRaw = analogRead(WATER_SENSOR_PIN);

    // Calculate water added for local tracking
    float waterAddedRaw = wLevelRaw - previousWaterLevelRaw;
    if (waterAddedRaw < 0) waterAddedRaw = 0; // Prevent negative additions if sensor fluctuates
    
    float waterAddedML = waterAddedRaw * ADC_TO_ML_FACTOR;
    totalCollectedML += waterAddedML;
    previousWaterLevelRaw = wLevelRaw;

    display.clearDisplay();
    display.setTextSize(1);
    
    if (isnan(h) || isnan(t)) {
      display.setCursor(0, 0);
      display.println("DHT Read Error");
    } else {
      display.setCursor(0, 0);
      display.print("Temp: "); display.print(t, 1); display.println(" C");
      display.setCursor(0, 15);
      display.print("Hum:  "); display.print(h, 1); display.println(" %");
    }

    display.setCursor(0, 35);
    display.print("Water Raw: "); display.print(wLevelRaw);
    display.setCursor(0, 50);
    display.print("Total mL:  "); display.print(totalCollectedML, 2);
    
    display.display();
    
    // Optional Serial Monitor Debugging
    Serial.print("Temp: "); Serial.print(t);
    Serial.print("C | Hum: "); Serial.print(h);
    Serial.print("% | Water Raw: "); Serial.print(wLevelRaw);
    Serial.print(" | Total mL: "); Serial.println(totalCollectedML);
  }
}
