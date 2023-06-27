#include <HX711.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DOUT_PIN 4   // DOUT pin of HX711 connected to ESP32 GPIO 4
#define CLK_PIN 5    // CLK pin of HX711 connected to ESP32 GPIO 5
#define BUZZER_PIN 13  // Buzzer pin connected to ESP32 GPIO 13

#define OLED_RESET 16  // OLED reset pin connected to ESP32 GPIO 16

#define THRESHOLD 1000.0 // Threshold value for IV fluid weight

HX711 scale(DOUT_PIN, CLK_PIN);  // Create an instance of the HX711 library

Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  scale.set_scale(1.0);  // Set calibration factor if necessary
  scale.tare();  // Reset the scale to 0

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize OLED display
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Smart Drip Device");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float weight = scale.get_units();  // Get weight in units specified by set_scale()

  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Weight: ");
  display.print(weight);
  display.println(" g");
  display.display();

  // Check if weight is below the threshold
  if (weight < THRESHOLD) {
    // Activate the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);  // Adjust delay as needed for the desired buzzer activation duration
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);  // Adjust delay as needed for the desired pause between buzzer activations

    // Display alert message on OLED display
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Fluid level low!");
    display.display();
    delay(2000);  // Adjust delay as needed for the desired display duration
    display.clearDisplay();
  }

  delay(1000);  // Adjust delay as needed for the desired weight checking interval
}
